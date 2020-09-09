#include "fmt/core.h"

#include "EntityManager.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Window.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/KeyboardControlComponent.hpp"
#include "components/TileComponent.hpp"
#include "components/MeshComponent.hpp"
#include "components/CollisionComponent.hpp"

EntityManager::EntityManager() = default;

EntityManager::~EntityManager() = default;

Entity& EntityManager::addEntity() {
    auto entity = registry.create();

    entities.emplace_back(new Entity(entities.size() + 1, entity));

    return *entities[entities.size() - 1];
}

Entity& EntityManager::addTile() {
    auto tile = registry.create();

    tiles.emplace_back(new Entity(tiles.size() + 1, tile));

    return *tiles[tiles.size() - 1];
}

void EntityManager::update(float deltaTime_) {
    for ( auto& entity : entities ) {
        Game::shaders["model"]->useShader();

        auto& tc = registry.get<TransformComponent>(entity->entity);
        tc.update();

        if ( entity->id == player.id ) {
            registry.get<KeyboardControlComponent>(entity->entity).update(deltaTime_);
        }

        registry.get<CollisionComponent>(entity->entity).update(b2Vec2{tc.position.x, tc.position.y});

        registry.get<SpriteComponent>(entity->entity).update(deltaTime_);
    }
}

void EntityManager::updateMap() {
    for ( auto& tile : tiles ) {
        registry.get<TileComponent>(tile->entity).update();
    }
}

void EntityManager::render() {
    for ( auto& entity : entities ) {
        Game::shaders["model"]->useShader();

        registry.get<TransformComponent>(entity->entity).render();
        registry.get<SpriteComponent>(entity->entity).render();
        registry.get<MeshComponent>(entity->entity).render();
    }
}

void EntityManager::renderMap() {
    for ( auto& tile : tiles ) {
        registry.get<TileComponent>(tile->entity).render();
        registry.get<MeshComponent>(tile->entity).render();
    }
}

Entity& EntityManager::getEntity(unsigned int id_) {
    return *entities[id_ - 1];
}

Entity& EntityManager::getTile(unsigned int id_) {
    return *tiles[id_ - 1];
}
