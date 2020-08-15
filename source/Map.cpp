#include <fstream>

#include "Map.hpp"
#include "Game.hpp"
#include "EntityManager.hpp"
#include "components/TileComponent.hpp"

Map::Map() = default;

Map::~Map() = default;

void Map::loadMap(const std::string& filePath_, glm::vec2 mapSize_, float tileSize_, const std::string &textureID_) {
    std::fstream mapFile;
    mapFile.open(filePath_);

    glm::vec2 tilePosition;
    tilePosition.y = (mapSize_.y / 2) * static_cast<float>(tileSize_);

    for ( int y = 0; y < static_cast<int>(mapSize_.y); y++ ) {
        tilePosition.x = -(mapSize_.x / 2) * static_cast<float>(tileSize_);

        for ( int x = 0; x < static_cast<int>(mapSize_.x); x++ ) {
            char ch;
            glm::vec2 uv;

            mapFile.get(ch);
            uv.y = static_cast<float>(atoi(&ch));

            mapFile.get(ch);
            uv.x = static_cast<float>(atoi(&ch));

            Map::addTile(tilePosition, tileSize_, textureID_);

            tilePosition.x += static_cast<float>(tileSize_);

            mapFile.ignore();
        }

        tilePosition.y -= static_cast<float>(tileSize_);
    }
}

void Map::addTile(glm::vec2 position_,float size_, const std::string &textureID_) {
    auto tile = Game::entityManager->addEntity();
    Game::entityManager->registry.emplace<TileComponent>(tile.entity, position_, size_, textureID_);
}
