#include "spdlog/spdlog.h"

#include "EntityManager.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Window.hpp"
#include "ContactListener.hpp"
#include "Game.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/KeyboardControlComponent.hpp"
#include "components/TileComponent.hpp"
#include "components/MeshComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/ProjectileEmitterComponent.hpp"
#include "components/ParticlesComponent.hpp"

EntityManager::EntityManager() = default;

EntityManager::~EntityManager() = default;

Entity& EntityManager::addEntity(EntityType type_) {
    auto entity = registry.create();

    entities.emplace_back(new Entity(entities.size() + 1, entity, type_));

    return *entities[entities.size() - 1];
}

Entity& EntityManager::addTile() {
    auto tile = registry.create();

    tiles.emplace_back(new Entity(tiles.size() + 1, tile, TILE));

    return *tiles[tiles.size() - 1];
}

void EntityManager::update(float deltaTime_) {
    for ( auto& entity : entities ) {
        Game::shaders["model"]->useShader();

        auto& tc = registry.get<TransformComponent>(entity->entity);
        tc.update();

        if ( entity->type == PLAYER ) {
            registry.get<KeyboardControlComponent>(entity->entity).update(deltaTime_);
        }

        if ( entity->type == PROJECTILE ) {
            registry.get<ProjectileEmitterComponent>(entity->entity).update(deltaTime_);
        }

        registry.get<CollisionComponent>(entity->entity).update(b2Vec2{tc.position.x, tc.position.y});

        registry.get<SpriteComponent>(entity->entity).update(deltaTime_);

        if ( entity->type == PROJECTILE ) {
            registry.get<ParticleComponent>(entity->entity).update(deltaTime_);
        }
    }
}

void EntityManager::updateMap() {
    for ( auto& tile : tiles ) {
        registry.get<TileComponent>(tile->entity).update();
    }
}

void EntityManager::render(const glm::mat4& proj, const glm::mat4& view) {
    for ( auto& entity : entities ) {
        Game::shaders["model"]->useShader();

        registry.get<TransformComponent>(entity->entity).render();
        registry.get<SpriteComponent>(entity->entity).render();

        if ( entity->type == PLAYER ) {
            Game::mesh["player"]->renderMesh();
        } else {
            Game::mesh["enemy"]->renderMesh();
        }

        if ( entity->type == PROJECTILE ) {
            registry.get<ParticleComponent>(entity->entity).render(proj, view);
        }
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

void EntityManager::clearBodys() {
    auto view = registry.view<CollisionComponent>();

    for ( auto& entity : view ) {
        auto& collisionC = registry.get<CollisionComponent>(entity);
        Game::contactListener->DestroyBody(collisionC.body);
    }
}

void EntityManager::clear() {
    spdlog::info("[Game] Clear entities");
    for ( auto& entity : entities ) {
        registry.destroy(entity->entity);
    }

    for ( auto& tile : tiles ) {
        registry.destroy(tile->entity);
    }

    registry.clear();
    entities.clear();
    tiles.clear();
}
