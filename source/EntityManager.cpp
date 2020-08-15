#include "fmt/core.h"

#include "EntityManager.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Window.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/KeyboardControlComponent.hpp"
#include "components/TileComponent.hpp"

EntityManager::EntityManager() = default;

EntityManager::~EntityManager() {
    for ( auto& entity : entities ) {
        delete entity;
    }

    registry.clear();
}

Entity& EntityManager::addEntity() {
    auto entity = registry.create();

    entities.emplace_back(new Entity(entities.size() + 1, entity));

    return *entities[entities.size() - 1];
}

void EntityManager::update(float deltaTime_) {
    auto view = Game::camera->viewMatrix(glm::vec3(0.0f, 0.0f, 0.0f));
    auto projection = Game::camera->projectionMatrix(90.0f, Game::window->windowSize());

    Game::shaders["tile"]->useShader();

    glUniformMatrix4fv(Game::shaders["tile"]->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(Game::shaders["tile"]->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    auto viewTiles = registry.view<TileComponent>();

    for ( auto tile : viewTiles ) {
        auto& tileComponent = registry.get<TileComponent>(tile);

        tileComponent.update();
    }

    Game::shaders["model"]->useShader();

    glUniformMatrix4fv(Game::shaders["model"]->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(Game::shaders["model"]->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    auto viewEntities = registry.view<TransformComponent, SpriteComponent, KeyboardControlComponent>();

    for ( auto entity : viewEntities ) {
        auto& transformComponent = registry.get<TransformComponent>(entity);
        auto& keyBoardComponent = registry.get<KeyboardControlComponent>(entity);
        auto& spriteComponent = registry.get<SpriteComponent>(entity);

        transformComponent.update();
        keyBoardComponent.update(deltaTime_);
        spriteComponent.update(deltaTime_);
    }
}

void EntityManager::render() {
    Game::shaders["tile"]->useShader();

    auto viewTiles = registry.view<TileComponent>();

    for ( auto tile : viewTiles ) {
        auto& tileComponent = registry.get<TileComponent>(tile);

        tileComponent.render();
        Game::mesh["tile"]->renderMesh();
    }

    Game::shaders["model"]->useShader();

    auto viewEntities = registry.view<TransformComponent, SpriteComponent>();

    for ( auto entity : viewEntities ) {
        auto& transformComponent = registry.get<TransformComponent>(entity);
        auto& spriteComponent = registry.get<SpriteComponent>(entity);

        transformComponent.render();
        spriteComponent.render();
        Game::mesh["entity"]->renderMesh();
    }
}

Entity& EntityManager::getEntity(unsigned int id_) {
    return *entities[id_ - 1];
}
