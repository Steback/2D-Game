#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <vector>

#include "entt/entt.hpp"

class TileComponent;

struct Entity {
    unsigned int id{};
    entt::entity entity{};

    Entity() = default;
    Entity(unsigned int id_, entt::entity entity_) : id(id_), entity(entity_) {  }
};

class EntityManager {
    public:
        EntityManager();
        ~EntityManager();
        Entity& addEntity();
        Entity& addTile();
        void update(float deltaTime_);
        void updateMap();
        void render();
        void renderMap();
        Entity& getEntity(unsigned int id_);
        Entity& getTile(unsigned int id_);

        entt::registry registry;

    private:
        std::vector<std::unique_ptr<Entity> > entities;
        std::vector<std::unique_ptr<Entity> > tiles;
};

#endif
