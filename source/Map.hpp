#ifndef MAP_HPP
#define MAP_HPP

#include <string>

#include "glm/glm.hpp"

class Map {
    public:
        Map();
        ~Map();

    private:
        unsigned int tileSize;
        glm::vec2 sizeMap;
        std::string filePath;
};

#endif
