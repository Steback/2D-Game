#include "Game.hpp"
#include "Window.hpp"

int main() {
    Game::init();

    while ( Game::window->isRunning() ) {
        Game::update();
        Game::render();
    }

    Game::destroy();

    return 0;
}