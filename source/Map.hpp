#ifndef MAP_HPP
#define MAP_HPP

#include <string>

#include "glm/glm.hpp"

class Map {
    public:
        Map();
        ~Map();
        static void loadMap(const std::string& filePath_, glm::vec2 mapSize_, unsigned tileSize_, const std::string &textureID_);
        static void addTile(glm::vec2 position_, unsigned int size_, const std::string& textureID_);

    private:

};

#endif
