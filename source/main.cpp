#include "Game.hpp"

int main() {
    Game game;

    game.init();

    while ( game.isRunning() ) {
        game.render();
    }

    game.destroy();

    return 0;
}