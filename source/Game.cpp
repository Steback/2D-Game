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
#include "Map.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/KeyboardControlComponent.hpp"
#include "components/TileComponent.hpp"

// static objects
std::unique_ptr<Window> Game::window;
std::map<std::string, std::unique_ptr<Shader> > Game::shaders;
std::unique_ptr<EntityManager> Game::entityManager;
std::unique_ptr<Camera> Game::camera;
std::unique_ptr<AssetsManager> Game::assetsManager;
std::map<std::string, std::unique_ptr<Mesh> > Game::mesh;

// Global variables
float lastFrame = 0;

Game::Game() = default;

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

    auto entity = entityManager->addEntity();

    entityManager->registry.emplace<TransformComponent>(entity.entity, glm::vec2(0.0f, 0.0f),
                                                        glm::vec2(32.0f * 0.5f * 0.1f, 32.0f * 0.5f * 0.1f),
                                                        5.0f);

    entityManager->registry.emplace<KeyboardControlComponent>(entity.entity, entity);

    entityManager->registry.emplace<SpriteComponent>(entity.entity,
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

    camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 10.0f));

    auto tile = entityManager->addEntity();
    entityManager->registry.emplace<TileComponent>(tile.entity, glm::vec2(0.0f, 0.0f), 32 * 0.1f, "jungle");

    mesh.emplace("tile", std::make_unique<Mesh>(std::vector<Vertex>{
            {glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f / 10, 0.0f) },
            {glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f / 3) },
            {glm::vec2(-1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f / 10, 1.0f / 3) },
            {glm::vec2(1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
    }, std::vector<GLuint> {
            1, 3, 2,
            0, 3, 2
    }));

//    Map::loadMap("levels/level-1.map", glm::vec2(25, 20), 32.0f * 0.1f, "jungle");
}

void Game::update() {
    glfwPollEvents();

    auto currentFrame = static_cast<float>(glfwGetTime());
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    entityManager->update(deltaTime);
}

void Game::render() {
    window->render();

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
