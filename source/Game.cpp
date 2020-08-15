#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "fmt/core.h"

#include "Game.hpp"
#include "Window.hpp"
#include "Constants.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "EntityManager.hpp"
#include "Camera.hpp"
#include "AssetsManager.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/KeyboardControlComponent.hpp"

// static objects
std::unique_ptr<Window> Game::window;
std::map<std::string, std::unique_ptr<Shader> > Game::shaders;
std::unique_ptr<Mesh> Game::mesh;
std::unique_ptr<EntityManager> Game::entityManager;
std::unique_ptr<Camera> Game::camera;
std::unique_ptr<AssetsManager> Game::assetsManager;

// Global variables
float lastFrame = 0;

Game::Game() = default;

Game::~Game() = default;

void Game::init() {
    window = std::make_unique<Window>();
    window->init(WINDOW_WIDTH, WINDOW_HEIGHT);

    shaders.emplace("model", std::make_unique<Shader>("shaders/model.vert", "shaders/model.frag"));

    mesh = std::make_unique<Mesh>( std::vector<Shape> {
            {glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.0f) },
            {glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.25f) },
            {glm::vec2(-1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.25f) },
            {glm::vec2(1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
    }, std::vector<GLuint> {
            1, 3, 2,
            0, 3, 2
    } );

    assetsManager = std::make_unique<AssetsManager>();
    assetsManager->addTexture("chopper-spritesheet", "assets/images/chopper-spritesheet.png");
    assetsManager->addTexture("jungle", "assets/tilemaps/jungle.png");
    assetsManager->loadTexture();

    entityManager = std::make_unique<EntityManager>();

    auto entity = entityManager->addEntity();
    entityManager->registry.emplace<TransformComponent>(entity.entity, glm::vec2(0.0f, 0.0f), glm::vec2(32.0f, 32.0f), 5.0f);
    entityManager->registry.emplace<KeyboardControlComponent>(entity.entity, entity);
    entityManager->registry.emplace<SpriteComponent>(entity.entity, assetsManager->getTexture("chopper-spritesheet"), true, 2, 4);

    camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 100.0f));
}

void Game::update() {
    glfwPollEvents();

    auto currentFrame = static_cast<float>(glfwGetTime());
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    shaders["model"]->useShader();

    auto view = camera->viewMatrix(glm::vec3(0.0f, 0.0f, 0.0f));
    auto projection = camera->projectionMatrix(90.0f, window->windowSize());

    glUniformMatrix4fv(shaders["model"]->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shaders["model"]->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    entityManager->update(deltaTime);
}

void Game::render() {
    window->render();

    entityManager->render();
    mesh->renderMesh();

    glUseProgram(0);

    window->swapBuffer();
}

void Game::destroy() {
    for ( auto& shader : shaders ) {
        shader.second->clearShader();
    }

    mesh->clearMesh();
    window->destroy();
}
