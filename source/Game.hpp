#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <map>

#include "box2d/b2_world.h"

#include "EntityManager.hpp"

class Window;
class Shader;
class Mesh;
class Texture;
class EntityManager;
class Camera;
class AssetsManager;
class ContactListener;
class Map;
class ParticleEmitter;

class Game {
    public:
        Game();
        ~Game();
        void init();
        void update() const;
        void render();
        void clear();

        static std::unique_ptr<Window> window;
        static std::map<std::string, std::unique_ptr<Shader> > shaders;
        static std::unique_ptr<EntityManager> entityManager;
        static std::unique_ptr<Camera> camera;
        static std::unique_ptr<AssetsManager> assetsManager;
        static std::unique_ptr<ContactListener> contactListener;
        static std::unique_ptr<Map> map;

    private:
        Entity player{};

        std::unique_ptr<ParticleEmitter> particleEmitter;
};

#endif
