#include <fstream>

#include "fmt/core.h"

#include "Map.hpp"
#include "Game.hpp"
#include "ContactListener.hpp"
#include "components/TileComponent.hpp"
#include "components/MeshComponent.hpp"

Map::Map() : type(MAP) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 0.0f);
    bodyDef.angle = 0.0f;

    body = Game::contactListener->CreateBody(&bodyDef);

    body->SetUserData(static_cast<void*>(&type));
}

Map::~Map() = default;

void Map::loadMap(const std::string& filePath_, glm::vec2 mapSize_, float tileSize_, const std::string &textureID_) {
    std::fstream mapFile;
    mapFile.open(filePath_);

    glm::vec2 tilePosition;
    tilePosition.y = (mapSize_.y / 2) * (tileSize_ * 2);

    std::vector<b2Vec2> points_wall_top;
    std::vector<b2Vec2> points_wall_left;
    std::vector<b2Vec2> points_wall_right;
    std::vector<b2Vec2> points_wall_bottom;

    for ( int y = 0; y < static_cast<int>(mapSize_.y); y++ ) {
        tilePosition.x = -(mapSize_.x / 2) * (tileSize_ * 2);

        for ( int x = 0; x < static_cast<int>(mapSize_.x); x++ ) {
            // SET POINTS FOR TOP MAP
            if ( y == 0 && x == 0 ) {
                points_wall_top.emplace_back(tilePosition.x - tileSize_, tilePosition.y + tileSize_);
                points_wall_left.emplace_back(tilePosition.x - tileSize_, tilePosition.y + tileSize_);
            }

            if ( y == 0 ) {
                points_wall_top.emplace_back(tilePosition.x + tileSize_, tilePosition.y + tileSize_);
            }

            // SET POINTS FOR LEFT MAP
            if ( y != 0 && x == 0 ) {
                points_wall_left.emplace_back(tilePosition.x - tileSize_, tilePosition.y - tileSize_);
            }

            // SET POINTS FOR RIGHT MAP
            if ( x == static_cast<int>(mapSize_.x) - 1 ) {
                points_wall_right.emplace_back(tilePosition.x + tileSize_, tilePosition.y - tileSize_);

                if ( y == 0 ) {
                    points_wall_right.emplace_back(tilePosition.x + tileSize_, tilePosition.y + tileSize_);
                }
            }

            // SET POINTS FOR BOTTOM MAP
            if ( y == static_cast<int>(mapSize_.y) - 1 ) {
                points_wall_bottom.emplace_back(tilePosition.x + tileSize_, tilePosition.y - tileSize_);

                if ( x == 0 ) {
                    points_wall_bottom.emplace_back(tilePosition.x - tileSize_, tilePosition.y - tileSize_);
                }
            }

            // SET SPRITE TILE
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

    // LOAD POINTS FOR TOP MAP
    b2ChainShape wall_top;
    wall_top.CreateLoop(&points_wall_top[0], points_wall_top.size());

    b2FixtureDef edgeShapeDef;
    edgeShapeDef.shape = &wall_top;
    edgeShapeDef.density = 1.0f;
    edgeShapeDef.restitution = 0.1f;

    body->CreateFixture(&edgeShapeDef);

    // LOAD POINTS FOR LEFT MAP
    b2ChainShape wall_left;
    wall_left.CreateLoop(&points_wall_left[0], points_wall_left.size());

    b2EdgeShape edge;

    edgeShapeDef.shape = &wall_left;
    edgeShapeDef.density = 1.0f;
    edgeShapeDef.restitution = 0.1f;

    body->CreateFixture(&edgeShapeDef);

    // LOAD POINTS FOR RIGHT MAP
    b2ChainShape wall_right;
    wall_right.CreateLoop(&points_wall_right[0], points_wall_right.size());

    edgeShapeDef.shape = &wall_right;
    edgeShapeDef.density = 1.0f;
    edgeShapeDef.restitution = 0.1f;

    body->CreateFixture(&edgeShapeDef);

    // LOAD POINTS FOR BOTTOM MAP
    b2ChainShape wall_bottom;
    wall_bottom.CreateLoop(&points_wall_bottom[0], points_wall_bottom.size());

    edgeShapeDef.shape = &wall_bottom;
    edgeShapeDef.density = 1.0f;
    edgeShapeDef.restitution = 0.1f;

    body->CreateFixture(&edgeShapeDef);

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
