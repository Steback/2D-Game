#include "Game.hpp"
#include "Window.hpp"

int main() {
    Game game;

    game.init();

    while ( Game::window->isRunning() ) {
        game.update();
        game.render();
    }

    return 0;
}