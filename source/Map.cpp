#include <fstream>

#include "fmt/core.h"

#include "Map.hpp"
#include "Game.hpp"
#include "components/TileComponent.hpp"

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
            glm::vec2 uv;

            mapFile.get(ch);
            uv.y = static_cast<float>(atoi(&ch));

            mapFile.get(ch);
            uv.x = static_cast<float>(atoi(&ch));

            Map::addTile(tilePosition, tileSize_, textureID_, glm::vec2(1.0f, 1.0f));

            tilePosition.x += (tileSize_ * 2);

            mapFile.ignore();
        }

        tilePosition.y -= (tileSize_ * 2);
    }
}

void Map::addTile(glm::vec2 position_,float size_, const std::string &textureID_, glm::vec2 uv_) {
    auto tile = Game::entityManager->addTile();
    Game::entityManager->registry.emplace<TileComponent>(tile.entity, position_, size_, textureID_, uv_);
}
