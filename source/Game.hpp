#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <vector>

class Window;
class Shader;
class Mesh;
class Texture;
class EntityManager;
class Camera;

class Game {
    public:
        Game();
        ~Game();
        void init();
        void update();
        void render();
        void destroy();
        bool isRunning();

        static std::vector<std::unique_ptr<Shader> > shaders;
        static std::unique_ptr<Mesh> mesh;
        static std::unique_ptr<EntityManager> entityManager;
        static std::unique_ptr<Camera> camera;

private:
        std::unique_ptr<Window> window;
        std::shared_ptr<Texture> texture;
};

#endif
