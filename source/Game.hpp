#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <map>

class Window;
class Shader;
class Mesh;
class Texture;
class EntityManager;
class Camera;
class AssetsManager;

class Game {
    public:
        Game();
        ~Game();
        static void init();
        static void update();
        static void render();
        static void destroy();

        static std::unique_ptr<Window> window;
        static std::map<std::string, std::unique_ptr<Shader> > shaders;
        static std::unique_ptr<Mesh> mesh;
        static std::unique_ptr<EntityManager> entityManager;
        static std::unique_ptr<Camera> camera;
        static std::unique_ptr<AssetsManager> assetsManager;

    private:

};

#endif
