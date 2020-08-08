#include "Game.hpp"

int main() {
    Game game;

    game.init();

    while ( game.isRunning() ) {
        game.update();
        game.render();
    }

    game.destroy();

    return 0;
}