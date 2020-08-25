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
#include "Camera.hpp"
#include "AssetsManager.hpp"
#include "Map.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/KeyboardControlComponent.hpp"

// static objects
std::unique_ptr<Window> Game::window;
std::map<std::string, std::unique_ptr<Shader> > Game::shaders;
std::unique_ptr<EntityManager> Game::entityManager;
std::unique_ptr<Camera> Game::camera;
std::unique_ptr<AssetsManager> Game::assetsManager;
std::map<std::string, std::unique_ptr<Mesh> > Game::mesh;

// Global variables
float lastFrame = 0;

Game::Game()  = default;

Game::~Game() = default;

void Game::init() {
    window = std::make_unique<Window>();
    window->init(WINDOW_WIDTH, WINDOW_HEIGHT);

    shaders.emplace("model", std::make_unique<Shader>("shaders/model.vert", "shaders/model.frag"));
    shaders.emplace("tile", std::make_unique<Shader>("shaders/tile.vert", "shaders/tile.frag"));

    assetsManager = std::make_unique<AssetsManager>();
    assetsManager->addTexture("chopper-spritesheet", "assets/images/chopper-spritesheet.png");
    assetsManager->addTexture("jungle", "assets/tilemaps/jungle.png");
    assetsManager->loadTexture();

    entityManager = std::make_unique<EntityManager>();

    player = entityManager->addEntity();

    entityManager->registry.emplace<TransformComponent>(player.entity, glm::vec2(0.0f, 0.0f),
                                                        glm::vec2(2.0f, 32.0f * 0.5f * 0.1f),
                                                        5.0f);

    entityManager->registry.emplace<KeyboardControlComponent>(player.entity, player);

    entityManager->registry.emplace<SpriteComponent>(player.entity,
                                                     assetsManager->getTexture("chopper-spritesheet"),
                                                     2, 4);

    mesh.emplace("entity", std::make_unique<Mesh>(std::vector<Vertex>{
            {glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f / 2, 0.0f) },
            {glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f / 4) },
            {glm::vec2(-1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f / 2, 1.0f / 4) },
            {glm::vec2(1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
    }, std::vector<GLuint> {
            1, 3, 2,
            0, 3, 2
    }));

    mesh.emplace("tile", std::make_unique<Mesh>(std::vector<Vertex>{
            {glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f / 10, 0.0f) },
            {glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f / 3) },
            {glm::vec2(-1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f / 10, 1.0f / 3) },
            {glm::vec2(1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
    }, std::vector<GLuint> {
            1, 3, 2,
            0, 3, 2
    }));

    camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 15.0f));

    Map::loadMap("levels/level-1.map", glm::vec2(25, 20), 4.0f, "jungle");
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

void Game::destroy() {
    for ( auto& m : mesh ) {
        m.second->clearMesh();
    }

    for ( auto& shader : shaders ) {
        shader.second->clearShader();
    }

    window->destroy();
}
