#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <map>

#include "EntityManager.hpp"
#include "box2d/b2_world.h"

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
        void init();
        void update() const;
        void render();

        static std::unique_ptr<Window> window;
        static std::map<std::string, std::unique_ptr<Shader> > shaders;
        static std::unique_ptr<EntityManager> entityManager;
        static std::unique_ptr<Camera> camera;
        static std::unique_ptr<AssetsManager> assetsManager;

    private:
        Entity player{};
};

#endif
