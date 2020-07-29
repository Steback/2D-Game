#include "Game.hpp"
#include "Window.hpp"
#include "Constants.hpp"

Game::Game() : window(nullptr) {  }

Game::~Game() = default;

void Game::init() {
    window = std::make_unique<Window>();

    window->init(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Game::render() {
    glfwPollEvents();

    window->render();

    window->swapBuffer();
}

void Game::destroy() {
    window->destroy();
}

bool Game::isrunning() {
    return window->isRunning();
}
