#ifndef GAME_HPP
#define GAME_HPP

#include <memory>

class Window;

class Game {
    public:
        Game();
        ~Game();
        void init();
        void render();
        void destroy();
        bool isrunning();

    private:
        std::unique_ptr<Window> window;
};

#endif
