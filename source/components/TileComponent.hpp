#ifndef TILE_COMPONENT_HPP
#define TILE_COMPONENT_HPP

#include <memory>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../Texture.hpp"
#include "../Game.hpp"
#include "../AssetsManager.hpp"
#include "../Shader.hpp"
#include "../Constants.hpp"

class TileComponent {
    public:
        glm::mat4 model;
        glm::vec2 position;
        float size;
        std::shared_ptr<Texture> texture;

        TileComponent(glm::vec2 position_, float size_, const std::string& textureID_)
            : position(position_), size(size_), texture(Game::assetsManager->getTexture(textureID_)) {  }

        ~TileComponent() = default;

        void update() {
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(position, 0.0f));
            model = glm::scale(model, glm::vec3(size, size, 0.0f));
            model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
        }

        void render() {
            glUniformMatrix4fv(Game::shaders["model"]->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));
            texture->useTexture();
        }
};

#endif
