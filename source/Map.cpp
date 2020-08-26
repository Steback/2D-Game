#include <fstream>

#include "fmt/core.h"

#include "Map.hpp"
#include "Game.hpp"
#include "components/TileComponent.hpp"
#include "components/MeshComponent.hpp"

Map::Map() = default;

Map::~Map() = default;

void Map::loadMap(const std::string& filePath_, glm::vec2 mapSize_, float tileSize_, const std::string &textureID_) {
    std::fstream mapFile;
    mapFile.open(filePath_);

    glm::vec2 tilePosition;
    tilePosition.y = (mapSize_.y / 2) * (tileSize_ * 2);

    for ( int y = 0; y < static_cast<int>(mapSize_.y); y++ ) {
        tilePosition.x = -(mapSize_.x / 2) * (tileSize_ * 2);

        for ( int x = 0; x < static_cast<int>(mapSize_.x); x++ ) {
            char ch;

            mapFile.get(ch);
            int uvY = atoi(&ch);

            mapFile.get(ch);
            int uvX = atoi(&ch);

            Map::addTile(tilePosition, tileSize_, textureID_, glm::vec2(uvX, uvY));

            tilePosition.x += (tileSize_ * 2);

            mapFile.ignore();
        }

        tilePosition.y -= (tileSize_ * 2);
    }

    mapFile.close();
}

void Map::addTile(glm::vec2 position_,float size_, const std::string &textureID_, const glm::vec2& uv_) {
    auto tile = Game::entityManager->addTile();
    auto& tileComponent = Game::entityManager->registry.emplace<TileComponent>(tile.entity, position_, size_, textureID_);

    auto spriteWidth = (tileComponent.texture->getImageSize().x / NUM_TILES_MAP_X) / tileComponent.texture->getImageSize().x;
    auto spriteHeight = (tileComponent.texture->getImageSize().y / NUM_TILES_MAP_Y) / tileComponent.texture->getImageSize().y;

    glm::vec2 texCoords = glm::vec2(spriteWidth * uv_.x, spriteHeight * uv_.y);

    Game::entityManager->registry.emplace<MeshComponent>(tile.entity, std::vector<Vertex>{
            {glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
             glm::vec2(1.0f / 10, 0.0f) + texCoords },
            {glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
             glm::vec2(0.0f, 1.0f / 3) + texCoords },
            {glm::vec2(-1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
             glm::vec2(1.0f / 10, 1.0f / 3) + texCoords },
            {glm::vec2(1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
             glm::vec2(0.0f, 0.0f) + texCoords },
    }, std::vector<GLuint> {
            1, 3, 2,
            0, 3, 2
    });
}
