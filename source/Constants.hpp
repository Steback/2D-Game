#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 720;

const int NUM_TILES_MAP_X = 10;
const int NUM_TILES_MAP_Y = 3;

const int MAX_CAMERA_VIEW_Y = 180;
const int MAX_CAMERA_VIEW_X = 300;

enum EntityType {
    PLAYER = 0,
    ENEMY = 1,
    TILE = 2,
    PROJECTILE = 3,
    START = 4,
    HELIPORT = 5,
};

#endif
