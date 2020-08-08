#include "fmt/core.h"

#include "EntityManager.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"

EntityManager::EntityManager() = default;

EntityManager::~EntityManager() {
    for ( auto& entity : entities ) {
        delete entity;
    }

    registry.clear();
}

Entity& EntityManager::addEntity() {

    auto entity = registry.create();

    if ( !registry.valid(entity) ) fmt::print("FACK");

    entities.emplace_back(new Entity(entities.size() + 1, entity));

    return *entities[entities.size() - 1];
}

void EntityManager::update(float deltaTime_) {
    auto viewEntities = registry.view<TransformComponent, SpriteComponent>();

    for ( auto entity : viewEntities ) {
        auto& transformComponent = registry.get<TransformComponent>(entity);
        auto& spriteComponent = registry.get<SpriteComponent>(entity);

        transformComponent.update(deltaTime_);
        spriteComponent.update(deltaTime_);
    }
}

void EntityManager::render() {
    auto viewEntities = registry.view<TransformComponent, SpriteComponent>();

    for ( auto entity : viewEntities ) {
        auto& transformComponent = registry.get<TransformComponent>(entity);
        auto& spriteComponent = registry.get<SpriteComponent>(entity);

        transformComponent.render();
        spriteComponent.render();
    }
}

Entity& EntityManager::getEntity(unsigned int id_) {
    return *entities[id_ - 1];
}
