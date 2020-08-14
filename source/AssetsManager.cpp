#include "AssetsManager.hpp"
#include "Texture.hpp"

AssetsManager::AssetsManager() = default;

AssetsManager::~AssetsManager() = default;

void AssetsManager::addTexture(const std::string &textureID_, const std::string &filePath_) {
    textures.emplace(textureID_, std::make_shared<Texture>(filePath_));
}

void AssetsManager::loadTexture() {
    for ( auto& texture : textures ) {
        texture.second->loadTexture();
    }
}

std::shared_ptr<Texture> AssetsManager::getTexture(const std::string &textureID_) {
    return textures[textureID_];
}
