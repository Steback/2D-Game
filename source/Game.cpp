#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "fmt/core.h"

#include "Game.hpp"
#include "Window.hpp"
#include "Constants.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "AssetsManager.hpp"
#include "Map.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/KeyboardControlComponent.hpp"
#include "components/MeshComponent.hpp"

// static objects
std::unique_ptr<Window> Game::window;
std::map<std::string, std::unique_ptr<Shader> > Game::shaders;
std::unique_ptr<EntityManager> Game::entityManager;
std::unique_ptr<Camera> Game::camera;
std::unique_ptr<AssetsManager> Game::assetsManager;

// Global variables
float lastFrame = 0;

Game::Game()  = default;

Game::~Game() = default;

void Game::init() {
    window = std::make_unique<Window>();
    window->init(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Init Shaders
    shaders.emplace("model", std::make_unique<Shader>("shaders/model.vert", "shaders/model.frag"));
    shaders.emplace("tile", std::make_unique<Shader>("shaders/tile.vert", "shaders/tile.frag"));
    shaders.emplace("modelStatic", std::make_unique<Shader>("shaders/modelStatic.vert", "shaders/modelStatic.frag"));

    // Init EntityManager
    entityManager = std::make_unique<EntityManager>();

    // Init Camera
    camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 200.0f));

    // Load textures
    assetsManager = std::make_unique<AssetsManager>();
    assetsManager->addTexture("chopper-spritesheet", "assets/images/chopper-spritesheet.png");
    assetsManager->addTexture("jungle", "assets/tilemaps/jungle.png");
    assetsManager->addTexture("tank-big-down", "assets/images/tank-big-down.png");
    assetsManager->loadTexture();

    // Load Map
    Map::loadMap("levels/level-1.map", glm::vec2(25, 20), 64.0f, "jungle");

    // Load player entity
    player = entityManager->addEntity();
    entityManager->player = player;

    entityManager->registry.emplace<TransformComponent>(player.entity, glm::vec2(0.0f, 0.0f),
                                                        glm::vec2(32.0f, 32.0f),
                                                        100.0f);

    entityManager->registry.emplace<KeyboardControlComponent>(player.entity, player);

    entityManager->registry.emplace<SpriteComponent>(player.entity,
                                                     assetsManager->getTexture("chopper-spritesheet"),
                                                     true, 2, 4);

    entityManager->registry.emplace<MeshComponent>(player.entity, std::vector<Vertex>{
            {glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f / 2, 0.0f) },
            {glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f / 4) },
            {glm::vec2(-1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f / 2, 1.0f / 4) },
            {glm::vec2(1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
    }, std::vector<GLuint> {
            1, 3, 2,
            0, 3, 2
    });

    // Load enemy entity
    auto enemy = entityManager->addEntity();
    entityManager->registry.emplace<TransformComponent>(enemy.entity, glm::vec2(2.0f, 2.0f),
                                                        glm::vec2(32.0f, 32.0f),
                                                        10.0f);

    entityManager->registry.emplace<SpriteComponent>(enemy.entity,
                                                     assetsManager->getTexture("tank-big-down"));

    entityManager->registry.emplace<MeshComponent>(enemy.entity, std::vector<Vertex>{
            {glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
            {glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },
            {glm::vec2(-1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
            {glm::vec2(1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
    }, std::vector<GLuint> {
            1, 3, 2,
            0, 3, 2
    });

}

void Game::update() const {
    glfwPollEvents();

    auto currentFrame = static_cast<float>(glfwGetTime());
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    auto& transformComponent = entityManager->registry.get<TransformComponent>(player.entity);

    camera->setCamPosition(transformComponent.position);

    auto view = camera->viewMatrix(glm::vec3(transformComponent.position, 0.0f));
    auto projection = camera->projectionMatrix(90.0f, Game::window->windowSize());

    shaders["tile"]->useShader();
    glUniformMatrix4fv(shaders["tile"]->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shaders["tile"]->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    entityManager->updateMap();

    shaders["model"]->useShader();
    glUniformMatrix4fv(shaders["model"]->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shaders["model"]->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    shaders["modelStatic"]->useShader();
    glUniformMatrix4fv(shaders["modelStatic"]->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shaders["modelStatic"]->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    entityManager->update(deltaTime);
}

void Game::render() {
    window->render();

    shaders["tile"]->useShader();
    entityManager->renderMap();

    shaders["model"]->useShader();
    entityManager->render();

    glUseProgram(0);

    window->swapBuffer();
}
