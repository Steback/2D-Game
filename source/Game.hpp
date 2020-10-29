#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <map>
#include <unordered_map>

#include "box2d/b2_world.h"
#include "glm/glm.hpp"
#include "NsGui/FontProperties.h"
#include "NsGui/IntegrationAPI.h"
#include "NsGui/IRenderer.h"
#include "NsGui/IView.h"
#include "NsGui/Grid.h"
#include "NsApp/ThemeProviders.h"
#include "NsRender/GLFactory.h"

#include "EntityManager.hpp"
#include "ParticleSystem.hpp"

class Window;
class Shader;
class Mesh;
class Texture;
class EntityManager;
class Camera;
class AssetsManager;
class ContactListener;
class Map;

class Game {
    public:
        Game();
        ~Game();
        void init();
        void initNoesis();
        void loadLevel(const std::string& levelName);
        void update();
        void render();
        void clear();

        static std::unique_ptr<Window> window;
        static std::map<std::string, std::unique_ptr<Shader> > shaders;
        static std::unique_ptr<EntityManager> entityManager;
        static std::unique_ptr<Camera> camera;
        static std::unique_ptr<AssetsManager> assetsManager;
        static std::unique_ptr<ContactListener> contactListener;
        static std::unique_ptr<Map> map;
        static std::unordered_map<std::string, std::unique_ptr<Mesh> > mesh;
        static Noesis::IView* view;

    private:
        Entity player{};
        glm::mat4 m_view;
        glm::mat4 m_proj;
        ParticleProps m_Particle;

        std::unique_ptr<ParticleSystem> particleEmitter;
};

#endif
