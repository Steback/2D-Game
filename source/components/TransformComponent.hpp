#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "fmt/core.h"

#include "../Game.hpp"
#include "../Shader.hpp"

class TransformComponent {
    public:
        TransformComponent(glm::vec2 position_, glm::vec2 size_, float velocity_, float angle_)
            : size(size_), position(position_), velocity(velocity_, velocity_), angle(glm::radians(angle_)) {  }

        ~TransformComponent() = default;

        void update() {
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(position, 0.0f));
            model = glm::scale(model, glm::vec3(size.x, size.y, 0.0f));
            model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
            model = glm::rotate(model, angle, glm::vec3(0.0, 0.0, 1.0));
        }

        void render() {
            glUniformMatrix4fv(Game::shaders["model"]->getUniformLocation("model"), 1, GL_FALSE,
                               glm::value_ptr(model));
        }

    public:
        glm::mat4 model;
        glm::vec2 size;
        glm::vec2 position;
        glm::vec2 velocity;
        float angle;
};

#endif