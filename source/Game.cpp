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
#include "Audio.hpp"
#include "gui/Gui.hpp"
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
std::unique_ptr<Gui> Game::gui;
std::unique_ptr<Audio> Game::audio;
GameGUI::State Game::state_;
bool Game::gameLoaded;
bool Game::gamePaused;
bool Game::backMainMenu;

// Global variables
float lastFrame = 0;
bool loadimage = true;

Game::Game() = default;

Game::~Game() = default;

void Game::init() {
    spdlog::info("[Game] Init");

    window = std::make_unique<Window>();
    window->init(WINDOW_WIDTH, WINDOW_HEIGHT);

    gui = std::make_unique<Gui>();
    gui->init();

    // Init Shaders
    shaders.emplace("model", std::make_unique<Shader>("assets/shaders/model.vert", "assets/shaders/model.frag"));
    shaders.emplace("particle", std::make_unique<Shader>("assets/shaders/particle.vert", "assets/shaders/particle.frag"));

    // Init EntityManager
    entityManager = std::make_unique<EntityManager>();

    // Init Camera
    camera = std::make_unique<Camera>(0.25f, -1.0f, 1.0f);

    assetsManager = std::make_unique<AssetsManager>();

    audio = std::make_unique<Audio>();

    gameLoaded = false;
    gamePaused = false;
    backMainMenu = false;
    playSound = false;

    audio->init("assets/sounds/helicopter.wav");
}

void Game::loadLevel(const std::string &levelName) {
    // Load textures
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

    keyBoardController();

    if ( state_ == GameGUI::State::Exit ) {
        window->windowShouldClose(true);
    }

    if ( state_ == GameGUI::State::Loading && !gameLoaded ) {
        loadLevel("Level1.lua");
        gameLoaded = true;
    }

    if ( backMainMenu ) {
        spdlog::info("[Game] Clear level");
        mesh.erase("enemy");
        mesh.erase("player");
        particleEmitter.reset();
        map.reset();
        entityManager->clear();
        assetsManager->clear();
        gameLoaded = false;
        backMainMenu = false;
    }

    if ( gamePaused ) {
        playSound = false;
        audio->play(playSound);
    }

    gui->update(glfwGetTime());

    auto windowSize = window->windowSize();
    gui->reshapeFunc(static_cast<int>(windowSize.x), static_cast<int>(windowSize.y));

    auto cursorPos = window->cursorPos();
    gui->mouseMoveFunc(static_cast<int>(cursorPos.x), static_cast<int>(cursorPos.y));

    auto currentFrame = static_cast<float>(glfwGetTime());
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if ( state_ == GameGUI::State::Game && gameLoaded ) {
        contactListener->Step(deltaTime, 0, 0);
        window->windowShouldClose(contactListener->GameOver());

        auto& playerTC = entityManager->registry.get<TransformComponent>(player.entity);

        m_view = camera->viewMatrix(playerTC.position);
    } else {
        m_view = camera->viewMatrix(glm::vec2(0.0f, 0.0f));
    }

    shaders["particle"]->useShader();
    glUniformMatrix4fv(shaders["particle"]->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(m_view));

    shaders["model"]->useShader();
    glUniformMatrix4fv(shaders["model"]->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(m_view));

    if ( state_ == GameGUI::State::Game && gameLoaded && !gamePaused ) {
        entityManager->updateMap();
        entityManager->update(deltaTime);
    }

    if ( state_ == GameGUI::State::Game && gameLoaded && !playSound && !gamePaused ) {
        playSound = true;
        audio->play(playSound);
    }
}

void Game::render() {
    window->render();

    if ( (state_ == GameGUI::State::Game || state_ == GameGUI::State::Pause) && gameLoaded ) {
        shaders["model"]->useShader();
        entityManager->renderMap();
        entityManager->render(m_proj, m_view);
    }

    gui->render();
    glUseProgram(0);

    window->swapBuffer();
}

void Game::clear() {
    spdlog::info("[Game] Clear and shutdown");
    gui->clear();

    entityManager->clearBodys();
}

void Game::keyBoardController() {
    auto keys = window->getKeys();

    if (keys[GLFW_KEY_ESCAPE] && (state_ == GameGUI::State::Game || state_ == GameGUI::State::Pause)) {
        spdlog::warn("Game Paused: {}", gamePaused);
        gamePaused = !gamePaused;
        Game::gui->m_view->KeyDown(Noesis::Key_Escape);
    }

    if (keys[GLFW_KEY_SPACE] && state_ == GameGUI::State::Loading) {
        Game::gui->m_view->KeyDown(Noesis::Key_Space);
    }
}
