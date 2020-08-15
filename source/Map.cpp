#include <fstream>

#include "Map.hpp"
#include "Game.hpp"
#include "EntityManager.hpp"
#include "Constants.hpp"
#include "components/TileComponent.hpp"
#include "components/MeshComponent.hpp"

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

            Map::addTile(tilePosition, tileSize_, textureID_, uv);

            tilePosition.x += static_cast<float>(tileSize_);

            mapFile.ignore();
        }

        tilePosition.y -= static_cast<float>(tileSize_);
    }
}

void Map::addTile(glm::vec2 position_,float size_, const std::string &textureID_, glm::vec2 uv_) {
    auto tile = Game::entityManager->addEntity();
    Game::entityManager->registry.emplace<TileComponent>(tile.entity, position_, size_, textureID_);
    Game::entityManager->registry.emplace<MeshComponent>(tile.entity, std::vector<Vertex>{
            {glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec2((1.0f / NUM_TILES_MAP_X) * uv_.x, (1.0f / NUM_TILES_MAP_Y) * uv_.y) },
            {glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec2((1.0f / NUM_TILES_MAP_X) * uv_.x, (1.0f / NUM_TILES_MAP_Y) * uv_.y) },
            {glm::vec2(-1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec2((1.0f / NUM_TILES_MAP_X) * uv_.x, (1.0f / NUM_TILES_MAP_Y) * uv_.y) },
            {glm::vec2(1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec2((1.0f / NUM_TILES_MAP_X) * uv_.x, (1.0f / NUM_TILES_MAP_Y) * uv_.y) },
    }, std::vector<GLuint> {
            1, 3, 2,
            0, 3, 2
    } );
}
