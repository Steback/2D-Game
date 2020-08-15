#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <memory>

#include "../Texture.hpp"
#include "../Game.hpp"
#include "../Shader.hpp"

class SpriteComponent {
    public:
        std::shared_ptr<Texture> texture{};
        int indexFrame = 0;
        float spriteOffsetX{};
        float spriteOffsetY{};
        float animatedFrame = 0;

        explicit SpriteComponent(std::shared_ptr<Texture> texture_, int spriteOffsetX_ = 1, int spriteOffsetY_ = 1)
            : texture(std::move(texture_)), spriteOffsetX(static_cast<float>(spriteOffsetX_)),
            spriteOffsetY(static_cast<float>(spriteOffsetY_)) {  }

        ~SpriteComponent() = default;

        void update(float deltaTime_) {
            animatedFrame += deltaTime_ * 10;

            glUniform1i(Game::shaders["model"]->getUniformLocation("spriteOffsetX"), animatedFrame);
            glUniform1i(Game::shaders["model"]->getUniformLocation("spriteOffsetY"), indexFrame);
            glUniform1f(Game::shaders["model"]->getUniformLocation("spriteWidth"),
                        (texture->getImageSize().x / spriteOffsetX) / texture->getImageSize().x);
            glUniform1f(Game::shaders["model"]->getUniformLocation("spriteHeight"),
                        (texture->getImageSize().y / spriteOffsetY) / texture->getImageSize().y);

            if ( animatedFrame > 1 ) animatedFrame = 0;
        }

        void render() {
            texture->useTexture();
        }
};

#endif