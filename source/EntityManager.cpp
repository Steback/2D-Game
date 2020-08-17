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

void EntityManager::updateMap() {
    auto viewTiles = registry.view<TileComponent>();

    for ( auto tile : viewTiles ) {
        auto& tileComponent = registry.get<TileComponent>(tile);

        tileComponent.update();
    }
}

void EntityManager::render() {
    auto viewEntities = registry.view<TransformComponent, SpriteComponent>();

    for ( auto entity : viewEntities ) {
        auto& transformComponent = registry.get<TransformComponent>(entity);
        auto& spriteComponent = registry.get<SpriteComponent>(entity);

        transformComponent.render();
        spriteComponent.render();
        Game::mesh["entity"]->renderMesh();
    }
}

void EntityManager::renderMap() {
    auto viewTiles = registry.view<TileComponent>();

    for ( auto tile : viewTiles ) {
        auto& tileComponent = registry.get<TileComponent>(tile);

        tileComponent.render();
        Game::mesh["tile"]->renderMesh();
    }
}

Entity& EntityManager::getEntity(unsigned int id_) {
    return *entities[id_ - 1];
}
