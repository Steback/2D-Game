#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../Game.hpp"
#include "../Shader.hpp"

class TransformComponent {
    public:
        glm::mat4 model;
         glm::vec2 size;
         glm::vec2 position;

        TransformComponent(glm::vec2 position_, glm::vec2 size_)
            : size(size_), position(position_) {  }

        ~TransformComponent() = default;

        void update(float deltaTime_) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(position, -1.0f));
            model = glm::scale(model, glm::vec3(size, 1.0f));
            model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
        }

        void render() {
            glUniformMatrix4fv(Game::shaders[0]->getUniformLocation("model"), 1, GL_FALSE,
                               glm::value_ptr(model));
        }

};

#endif