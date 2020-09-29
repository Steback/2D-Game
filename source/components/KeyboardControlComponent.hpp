#ifndef KEYBOARD_CONTROL_COMPONENT_HPP
#define KEYBOARD_CONTROL_COMPONENT_HPP

#include "glm/glm.hpp"

#include "../Game.hpp"
#include "../Window.hpp"
#include "../EntityManager.hpp"
#include "../Map.hpp"

class KeyboardControlComponent {
    public:
        Entity entity;

        explicit KeyboardControlComponent(Entity entity_) : entity(entity_) {  }

        ~KeyboardControlComponent() = default;

        void update(float deltaTime_) const {
            auto keys = Game::window->getKeys();
            auto& transformComponent = Game::entityManager->registry.get<TransformComponent>(entity.entity);
            auto& spriteComponent = Game::entityManager->registry.get<SpriteComponent>(entity.entity);

            if ( keys[GLFW_KEY_W] ) {
                if ( transformComponent.position.y >= Game::map->getTopBorder() - (transformComponent.size.y / 2) ) {
                    transformComponent.position.y = Game::map->getTopBorder() - (transformComponent.size.y / 2);
                } else {
                    transformComponent.position.y += (transformComponent.velocity * deltaTime_);
                }

                spriteComponent.indexFrame = 3;
            }

            if ( keys[GLFW_KEY_S] ) {
                if ( transformComponent.position.y <= Game::map->getBottomBorder() + (transformComponent.size.y / 2) ) {
                    transformComponent.position.y = Game::map->getBottomBorder() + (transformComponent.size.y / 2);
                } else {
                    transformComponent.position.y -= (transformComponent.velocity * deltaTime_);
                }

                spriteComponent.indexFrame = 0;
            }

            if ( keys[GLFW_KEY_A] ) {
                if ( transformComponent.position.x <= Game::map->getLeftBorder() + (transformComponent.size.x / 2) ) {
                    transformComponent.position.x = Game::map->getLeftBorder() + (transformComponent.size.x / 2);
                } else {
                    transformComponent.position.x -= (transformComponent.velocity * deltaTime_);
                }

                spriteComponent.indexFrame = 2;
            }

            if ( keys[GLFW_KEY_D] ) {
                if ( transformComponent.position.x >= Game::map->getRightBorder() - (transformComponent.size.x / 2) ) {
                    transformComponent.position.x = Game::map->getRightBorder() - (transformComponent.size.x / 2);
                } else {
                    transformComponent.position.x += (transformComponent.velocity * deltaTime_);
                }

                spriteComponent.indexFrame = 1;
            }
        }
};

#endif
