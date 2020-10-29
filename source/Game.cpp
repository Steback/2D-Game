#include "glm/gtc/type_ptr.hpp"
#include "spdlog/spdlog.h"

#include "Game.hpp"
#include "Window.hpp"
#include "Constants.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "AssetsManager.hpp"
#include "ContactListener.hpp"
#include "LuaManager.hpp"
#include "Map.hpp"
#include "Mesh.hpp"
#include "components/TransformComponent.hpp"

// static objects
std::unique_ptr<Window> Game::window;
std::map<std::string, std::unique_ptr<Shader> > Game::shaders;
std::unique_ptr<EntityManager> Game::entityManager;
std::unique_ptr<Camera> Game::camera;
std::unique_ptr<AssetsManager> Game::assetsManager;
std::unique_ptr<ContactListener> Game::contactListener;
std::unique_ptr<Map> Game::map;
std::unordered_map<std::string, std::unique_ptr<Mesh> > Game::mesh;
Noesis::IView* Game::view;

// Global variables
float lastFrame = 0;

static void ReshapeFunc(int width, int height) {
    Game::view->SetSize(width, height);
}

static void MouseMoveFunc(int x, int y) {
    Game::view->MouseMove(x, y);
}

Game::Game() = default;

Game::~Game() = default;

void Game::init() {
    spdlog::info("[Game] Init");

    window = std::make_unique<Window>();
    window->init(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Init Shaders
    shaders.emplace("model", std::make_unique<Shader>("assets/shaders/model.vert", "assets/shaders/model.frag"));
    shaders.emplace("particle", std::make_unique<Shader>("assets/shaders/particle.vert", "assets/shaders/particle.frag"));

    // Init EntityManager
    entityManager = std::make_unique<EntityManager>();

    // Init Camera
    camera = std::make_unique<Camera>(0.25f, -1.0f, 1.0f);

    initNoesis();

//    loadLevel("Level1.lua");
}

void Game::initNoesis() {
    Noesis::SetLogHandler([](const char*, uint32_t, uint32_t level, const char*, const char* msg)
                          {
                              // [TRACE] [DEBUG] [INFO] [WARNING] [ERROR]
                              std::array<char, 5> prefixes = { 'T',
                                                               'D',
                                                               'I',
                                                               'W',
                                                               'E' };

                              switch (prefixes[level]) {
                                  case 'T':
                                      spdlog::trace("[NOESIS] {}" , msg); break;
                                  case 'D':
                                      spdlog::debug("[NOESIS] {}" , msg); break;
                                  case 'I':
                                      spdlog::info("[NOESIS] {}" , msg); break;
                                  case 'W':
                                      spdlog::warn("[NOESIS] {}" , msg); break;
                                  case 'E':
                                      spdlog::error("[NOESIS] {}" , msg); break;
                              }
                          });

    Noesis::GUI::Init(NS_LICENSE_NAME, NS_LICENSE_KEY);

    NoesisApp::SetThemeProviders();
    Noesis::GUI::LoadApplicationResources("Theme/NoesisTheme.DarkBlue.xaml");

    Noesis::Ptr<Noesis::Grid> xaml(Noesis::GUI::ParseXaml<Noesis::Grid>(R"(
        <Grid xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation">
            <Grid.Background>
                <LinearGradientBrush StartPoint="0,0" EndPoint="0,1">
                    <GradientStop Offset="0" Color="#FF123F61"/>
                    <GradientStop Offset="0.6" Color="#FF0E4B79"/>
                    <GradientStop Offset="0.7" Color="#FF106097"/>
                </LinearGradientBrush>
            </Grid.Background>
            <Viewbox>
                <StackPanel Margin="50">
                    <Button Content="Hello World!" Margin="0,30,0,0"/>
                    <Rectangle Height="5" Margin="-10,20,-10,0">
                        <Rectangle.Fill>
                            <RadialGradientBrush>
                                <GradientStop Offset="0" Color="#40000000"/>
                                <GradientStop Offset="1" Color="#00000000"/>
                            </RadialGradientBrush>
                        </Rectangle.Fill>
                    </Rectangle>
                </StackPanel>
            </Viewbox>
        </Grid>
    )"));

    view = Noesis::GUI::CreateView(xaml).GiveOwnership();
    view->SetFlags(Noesis::RenderFlags_PPAA | Noesis::RenderFlags_LCD);

    view->GetRenderer()->Init(NoesisApp::GLFactory::CreateDevice(false));
}

void Game::loadLevel(const std::string &levelName) {
    // Load textures
    assetsManager = std::make_unique<AssetsManager>();
    assetsManager->loadSprites("assets/images.xml");
    assetsManager->loadTextures();

    // Init contact listener
    contactListener = std::make_unique<ContactListener>();

    spdlog::info("[Game] Load level: {}", levelName);

    // Init map
    map = std::make_unique<Map>();

    // Load player entity
    LuaManager::loadFile("levels/" + levelName, player);

    particleEmitter = std::make_unique<ParticleSystem>();

    m_proj = camera->projectionMatrix(Game::window->windowSize());

    shaders["model"]->useShader();
    glUniformMatrix4fv(shaders["model"]->getUniformLocation("projection"), 1, GL_FALSE,
                       glm::value_ptr(m_proj));

    shaders["particle"]->useShader();
    glUniformMatrix4fv(shaders["particle"]->getUniformLocation("projection"), 1, GL_FALSE,
                       glm::value_ptr(m_proj));

    mesh["player"] = std::make_unique<Mesh>(std::vector<Vertex>{
            {glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec2(1.0f / 2, 0.0f) },
            {glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec2(0.0f, 1.0f / 4) },
            {glm::vec2(-1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec2(1.0f / 2, 1.0f / 4) },
            {glm::vec2(1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec2(0.0f, 0.0f) },
    }, std::vector<GLuint> {
            1, 3, 2,
            0, 3, 2
    });

    mesh["enemy"] = std::make_unique<Mesh>(std::vector<Vertex>{
            {glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec2(1.0f, 0.0f) },
            {glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec2(0.0f, 1.0f) },
            {glm::vec2(-1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec2(1.0f, 1.0f) },
            {glm::vec2(1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                    glm::vec2(0.0f, 0.0f) },
    }, std::vector<GLuint> {
            1, 3, 2,
            0, 3, 2
    });
}

void Game::update() {
    glfwPollEvents();

    view->Update(glfwGetTime() / 1000.0);

    view->GetRenderer()->UpdateRenderTree();
    view->GetRenderer()->RenderOffscreen();

    auto windowSize = window->windowSize();
    ReshapeFunc(static_cast<int>(windowSize.x), static_cast<int>(windowSize.y));

    auto cursorPos = window->cursorPos();
    MouseMoveFunc(static_cast<int>(cursorPos.x), static_cast<int>(cursorPos.y));

    //    window->windowShouldClose(contactListener->GameOver());

    auto currentFrame = static_cast<float>(glfwGetTime());
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

//    contactListener->Step(deltaTime, 0, 0);

//    auto& playerTC = entityManager->registry.get<TransformComponent>(player.entity);

    m_view = camera->viewMatrix(glm::vec2(0.0f, 0.0f));

    shaders["particle"]->useShader();
    glUniformMatrix4fv(shaders["particle"]->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(m_view));

    shaders["model"]->useShader();
    glUniformMatrix4fv(shaders["model"]->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(m_view));

//    entityManager->updateMap();
//    entityManager->update(deltaTime);
}

void Game::render() {
    window->render();

    shaders["model"]->useShader();
//    entityManager->renderMap();
//    entityManager->render(m_proj, m_view);

    view->GetRenderer()->Render();

    glUseProgram(0);

    window->swapBuffer();
}

void Game::clear() {
    entityManager->clearBodys();
}
