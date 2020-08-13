#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "fmt/core.h"

#include "Game.hpp"
#include "Window.hpp"
#include "Constants.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "EntityManager.hpp"
#include "Camera.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"

// static objects
std::vector<std::unique_ptr<Shader> > Game::shaders;
std::unique_ptr<Mesh> Game::mesh;
std::unique_ptr<EntityManager> Game::entityManager;
std::unique_ptr<Camera> Game::camera;

// Global variables
float lastFrame = 0;

Game::Game() : window(nullptr) {  }

Game::~Game() = default;

void Game::init() {
    window = std::make_unique<Window>();
    window->init(WINDOW_WIDTH, WINDOW_HEIGHT);

    shaders.emplace_back( std::make_unique<Shader>("shaders/model.vert", "shaders/model.frag") );

    mesh = std::make_unique<Mesh>( std::vector<Shape> {
            {glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.0f) },
            {glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.25f) },
            {glm::vec2(-1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 0.25f) },
            {glm::vec2(1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
    }, std::vector<GLuint> {
            1, 3, 2,
            0, 3, 2
    } );

    texture = std::make_shared<Texture>("assets/images/chopper-spritesheet.png");
    texture->loadTexture();

    entityManager = std::make_unique<EntityManager>();

    auto entity = entityManager->addEntity();

    entityManager->registry.emplace<TransformComponent>(entity.entity, glm::vec2(0.0f, 0.0f), glm::vec2(32.0f, 32.0f));
    entityManager->registry.emplace<SpriteComponent>(entity.entity, texture, true, 2, 4);

    camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 100.0f));
}

void Game::update() {
    glfwPollEvents();

    auto currentFrame = static_cast<float>(glfwGetTime());
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    shaders[0]->useShader();

    auto view = camera->viewMatrix(glm::vec3(0.0f, 0.0f, 0.0f));
    auto projection = camera->projectionMatrix(90.0f, window->windowSize());

    glUniformMatrix4fv(shaders[0]->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shaders[0]->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

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
    shaders[0]->clearShader();
    mesh->clearMesh();
    window->destroy();
}

bool Game::isRunning() {
    return window->isRunning();
}
