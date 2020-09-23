#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "fmt/core.h"
#include "tinyxml2.h"

#include "Game.hpp"
#include "Window.hpp"
#include "Constants.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "AssetsManager.hpp"
#include "ContactListener.hpp"
#include "LuaManager.hpp"
#include "components/TransformComponent.hpp"

// static objects
std::unique_ptr<Window> Game::window;
std::map<std::string, std::unique_ptr<Shader> > Game::shaders;
std::unique_ptr<EntityManager> Game::entityManager;
std::unique_ptr<Camera> Game::camera;
std::unique_ptr<AssetsManager> Game::assetsManager;
std::unique_ptr<ContactListener> Game::contactListener;

// Global variables
float lastFrame = 0;

Game::Game() = default;

Game::~Game() = default;

void Game::init() {
    window = std::make_unique<Window>();
    window->init(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Init Shaders
    shaders.emplace("model", std::make_unique<Shader>("shaders/model.vert", "shaders/model.frag"));

    // Init EntityManager
    entityManager = std::make_unique<EntityManager>();

    // Init Camera
    camera = std::make_unique<Camera>(4, -1.0f, 1.0f);

    // Load textures
    assetsManager = std::make_unique<AssetsManager>();
    assetsManager->loadSprites("assets/images.xml");
    assetsManager->loadTextures();

    // Init contact listener
    contactListener = std::make_unique<ContactListener>();

    // Load player entity
    LuaManager::loadFile("levels/Level1.lua", player);
}

void Game::update() const {
    glfwPollEvents();

    window->windowShouldClose(contactListener->GameOver());

    auto currentFrame = static_cast<float>(glfwGetTime());
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    contactListener->Step(deltaTime, 0, 0);

    auto& transformComponent = entityManager->registry.get<TransformComponent>(player.entity);

    fmt::print("{}, {}\n", transformComponent.position.x, transformComponent.position.y);

    auto view = camera->viewMatrix(glm::vec2(transformComponent.position));
    auto projection = camera->projectionMatrix(Game::window->windowSize());

    shaders["model"]->useShader();
    glUniformMatrix4fv(shaders["model"]->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shaders["model"]->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    entityManager->updateMap();
    entityManager->update(deltaTime);
}

void Game::render() {
    window->render();

    shaders["model"]->useShader();

    entityManager->renderMap();
    entityManager->render();

    glUseProgram(0);

    window->swapBuffer();
}

void Game::clear() {
    entityManager->clearBodys();
}
