#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 720;

const int NUM_TILES_MAP_X = 10;
const int NUM_TILES_MAP_Y = 3;

enum EntityType {
    PLAYER = 1,
    ENEMY = 1
};

enum EntityCategory {
    PLAYER_CATEGORY = 0x0002,
    ENEMY_CATEGORY = 0x0004
};

enum EntityMask {
    PLAYER_MASK = 0x0004,
    ENEMY_MASK = 0x0004
};

enum EntityIndex {
    COLLIDE = 1,
    NO_COLLIDE = -1
};

#endif
