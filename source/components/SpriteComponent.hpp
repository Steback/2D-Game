#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <memory>

#include "../Texture.hpp"
#include "../Game.hpp"
#include "../Shader.hpp"
#include "../AssetsManager.hpp"
#include "MeshComponent.hpp"

class SpriteComponent {
    public:
        std::shared_ptr<Texture> texture{};
        int indexFrame{};
        float spriteOffsetX{};
        float spriteOffsetY{};
        float animatedFrame{};
        bool isAnimated;
        float spriteWidth;
        float spriteHeight;
        unsigned int ownerID;
        float deltaTime{};

        explicit SpriteComponent(unsigned int ownerID_, const std::string& textureID_, bool isAnimated_ = false,
                                 int spriteOffsetX_ = 1, int spriteOffsetY_ = 1)
                                 : ownerID(ownerID_), texture(Game::assetsManager->getTexture(textureID_)),
                                 isAnimated(isAnimated_), spriteOffsetX(static_cast<float>(spriteOffsetX_)),
            spriteOffsetY(static_cast<float>(spriteOffsetY_)) {
            spriteWidth = (texture->getImageSize().x / spriteOffsetX) / texture->getImageSize().x;
            spriteHeight = (texture->getImageSize().y / spriteOffsetY) / texture->getImageSize().y;
        }

        ~SpriteComponent() = default;

        void update(float deltaTime_) {
            if ( isAnimated ) {
                deltaTime += deltaTime_ * 10;

                if ( deltaTime > 0.5f ) animatedFrame = 1;

                glm::vec2 texCoords = glm::vec2(spriteWidth * animatedFrame, spriteHeight * static_cast<float>(indexFrame));

                std::vector<glm::vec2> textureCoords {
                        glm::vec2(1.0f / spriteOffsetX, 0.0f) + texCoords,
                        glm::vec2(0.0f, 1.0f / spriteOffsetY) + texCoords,
                        glm::vec2(1.0f / spriteOffsetX, 1.0f / spriteOffsetY) + texCoords,
                        glm::vec2(0.0f, 0.0f) + texCoords
                };

                auto& meshComponent = Game::entityManager->registry.get<MeshComponent>(Game::entityManager->getEntity(ownerID).entity);
                meshComponent.mesh.setTextureCoords(textureCoords);

                if ( deltaTime > 1 ) {
                    animatedFrame = 0;
                    deltaTime = 0;
                }
            }
        }

        void render() {
            texture->useTexture();
        }
};

#endif