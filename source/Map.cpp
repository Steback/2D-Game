#include <fstream>

#include "Map.hpp"
#include "Game.hpp"
#include "EntityManager.hpp"
#include "components/TileComponent.hpp"

Map::Map() = default;

Map::~Map() = default;

void Map::loadMap(const std::string& filePath_, glm::vec2 mapSize_, unsigned int tileSize_, const std::string &textureID_) {
    std::fstream mapFile;
    mapFile.open(filePath_);

    glm::vec2 tilePosition;
    tilePosition.x = -(mapSize_.x / 2) * static_cast<float>(tileSize_);
    tilePosition.y = (mapSize_.y / 2) * static_cast<float>(tileSize_);

    for ( int y = 0; y < static_cast<int>(mapSize_.y); y++ ) {
        for ( int x = 0; x < static_cast<int>(mapSize_.x); x++ ) {
            char ch;

            mapFile.get(ch);

            mapFile.get(ch);

            Map::addTile(tilePosition, tileSize_, textureID_);

            tilePosition.x += static_cast<float>(tileSize_);
            tilePosition.y -= static_cast<float>(tileSize_);

            mapFile.ignore();
        }
    }
}

void Map::addTile(glm::vec2 position_, unsigned int size_, const std::string &textureID_) {
    auto tile = Game::entityManager->addEntity();
    Game::entityManager->registry.emplace<TileComponent>(tile.entity, position_, size_, textureID_);
}
