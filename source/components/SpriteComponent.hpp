#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <memory>

#include "../Texture.hpp"
#include "../Game.hpp"

class SpriteComponent {
    public:
        std::shared_ptr<Texture> texture{};
        bool isAnimated{};
        int indexFrame = 0;
        int spriteOffsetX{};
        int spriteOffsetY{};

        explicit SpriteComponent(std::shared_ptr<Texture> texture_)
            : texture(std::move(texture_)) {  }

        explicit SpriteComponent(std::shared_ptr<Texture> texture_, bool isAnimated_ = false, int spriteOffsetX_ = 1, int spriteOffsetY_ = 1)
            : texture(std::move(texture_)), isAnimated(isAnimated_), spriteOffsetX(spriteOffsetX_), spriteOffsetY(spriteOffsetY_)  {  }

        ~SpriteComponent() = default;

        void update(float deltaTime_) {
            indexFrame = static_cast<int>(deltaTime_) * 10;

            glUniform1i(Game::shaders[0]->getUniformLocation("spriteOffsetY"), 0);
            glUniform1i(Game::shaders[0]->getUniformLocation("spriteOffsetX"), indexFrame);
            glUniform1f(Game::shaders[0]->getUniformLocation("spriteWidth"), (texture->getImageSize().x / 2) / texture->getImageSize().x);
            glUniform1f(Game::shaders[0]->getUniformLocation("spriteHeight"), (texture->getImageSize().y / 4) / texture->getImageSize().y);
        }

        void render() {
            texture->useTexture();
        }
};

#endif