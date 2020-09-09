#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 720;

const int NUM_TILES_MAP_X = 10;
const int NUM_TILES_MAP_Y = 3;

enum LayerType {
    TILE_MAP_LAYER = 0,
    VEGETATION_LAYER = 1,
    ENEMY_LAYER = 2,
    OBSTACLE_LAYER = 3,
    PLAYER_LAYER = 4,
    PROJECTILE_LAYER = 5,
};

const std::int32_t k_largeGroup = -1;
const std::int32_t k_boxCategory = 0x0004;
const std::int32_t k_boxMask = 0xFFFF ^ 0x0002;

#endif
