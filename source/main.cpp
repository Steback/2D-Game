#include "Game.hpp"

int main() {
    Game game;

    game.init();

    while ( game.isrunning() ) {
        game.render();
    }

    game.destroy();

    return 0;
}