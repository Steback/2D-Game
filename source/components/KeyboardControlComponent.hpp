#ifndef KEYBOARD_CONTROL_COMPONENT_HPP
#define KEYBOARD_CONTROL_COMPONENT_HPP

#include "glm/glm.hpp"

#include "../Game.hpp"
#include "../Window.hpp"
#include "../EntityManager.hpp"

class KeyboardControlComponent {
    public:
        Entity entity;

        explicit KeyboardControlComponent(Entity entity_) : entity(entity_) {  }

        ~KeyboardControlComponent() = default;

        void update(float deltaTime_) const {
            auto keys = Game::window->getKeys()
            auto& transformComponent = Game::entityManager->registry.get<TransformComponent>(entity.entity);

            if ( keys[GLFW_KEY_W] ) {
                transformComponent.position.y += (transformComponent.velocity * deltaTime_);
                glUniform1i(Game::shaders[0]->getUniformLocation("spriteOffsetY"), 3);
            }

            if ( keys[GLFW_KEY_S] ) {
                transformComponent.position.y -= (transformComponent.velocity * deltaTime_);
                glUniform1i(Game::shaders[0]->getUniformLocation("spriteOffsetY"), 0);
            }

            if ( keys[GLFW_KEY_A] ) {
                transformComponent.position.x -= (transformComponent.velocity * deltaTime_);
                glUniform1i(Game::shaders[0]->getUniformLocation("spriteOffsetY"), 2);
            }

            if ( keys[GLFW_KEY_D] ) {
                transformComponent.position.x += (transformComponent.velocity * deltaTime_);
                glUniform1i(Game::shaders[0]->getUniformLocation("spriteOffsetY"), 1);
            }
        }
};

#endif
