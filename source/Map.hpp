#ifndef MAP_HPP
#define MAP_HPP

#include <string>

#include "glm/glm.hpp"
#include "box2d/box2d.h"
#include "box2d/b2_shape.h"

#include "Constants.hpp"

class Map {
    public:
        Map();
        ~Map();
        void loadMap(const std::string& filePath_, glm::vec2 mapSize_, float tileSize_, const std::string &textureID_);

    private:
        b2Body* body;
        EntityType type;

        static void addTile(glm::vec2 position_, float size_, const std::string& textureID_, const glm::vec2& uv_);
};

#endif
