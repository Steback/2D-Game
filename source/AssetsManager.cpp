#include "tinyxml2.h"
#include "spdlog/spdlog.h"

#include "AssetsManager.hpp"
#include "Texture.hpp"

AssetsManager::AssetsManager() = default;

AssetsManager::~AssetsManager() = default;

void AssetsManager::addTexture(const std::string &textureID_, const std::string &filePath_) {
    textures.emplace(textureID_, std::make_shared<Texture>(filePath_));
}

void AssetsManager::loadTextures() {
    for ( auto& texture : textures ) {
        texture.second->loadTexture();
    }
}

std::shared_ptr<Texture> AssetsManager::getTexture(const std::string &textureID_) {
    return textures[textureID_];
}

void AssetsManager::loadSprites(const std::string &filePath_) {
    tinyxml2::XMLDocument assets;

    if ( assets.LoadFile(filePath_.c_str()) != tinyxml2::XML_SUCCESS ) {
        spdlog::error("[TinyXML2] Error loading XML file\n");
    }

    tinyxml2::XMLNode* sprite = assets.RootElement()->FirstChild();

    while ( sprite != nullptr ) {
        addTexture( sprite->FirstChildElement("name")->FirstChild()->Value(),
                                   sprite->FirstChildElement("path")->FirstChild()->Value() );

        sprite = sprite->NextSibling();
    }
}

void AssetsManager::clear() {
    textures.clear();
}
