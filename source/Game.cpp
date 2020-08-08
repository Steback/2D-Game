#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "fmt/core.h"

#include "Game.hpp"
#include "Window.hpp"
#include "Constants.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "EntityManager.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"

// static objects
std::vector<std::unique_ptr<Shader> > Game::shaders;
std::unique_ptr<Mesh> Game::mesh;
std::unique_ptr<EntityManager> Game::entityManager;

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

    entityManager->registry.emplace<TransformComponent>(entity.entity, glm::vec2(0.4f, 0.4f), glm::vec2(1.0f, 1.0f));
    entityManager->registry.emplace<SpriteComponent>(entity.entity, texture, true, 2, 4);
}

void Game::update() {
    auto currentFrame = static_cast<float>(glfwGetTime());
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    shaders[0]->useShader();

    entityManager->update(deltaTime);
}

void Game::render() {
    glfwPollEvents();

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
