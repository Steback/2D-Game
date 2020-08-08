#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <vector>

#include "entt/entt.hpp"

struct Entity {
    unsigned int id;
    entt::entity entity;

    Entity(unsigned int id_, entt::entity entity_) : id(id_), entity(entity_) {  }
};

class EntityManager {
    public:
        EntityManager();
        ~EntityManager();
        Entity& addEntity();
        void update(float deltaTime_);
        void render();
        Entity& getEntity(unsigned int id_);

        entt::registry registry;

    private:
        std::vector<Entity* > entities;
};

#endif