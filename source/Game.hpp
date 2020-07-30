#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <vector>

class Window;
class Shader;
class Mesh;
class Texture;

class Game {
    public:
        Game();
        ~Game();
        void init();
        void render();
        void destroy();
        bool isRunning();

    private:
        std::unique_ptr<Window> window;
        std::vector<std::unique_ptr<Shader> > shaders;
        std::unique_ptr<Mesh> mesh;
        std::unique_ptr<Texture> texture;
};

#endif
