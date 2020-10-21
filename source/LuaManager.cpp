#include "sol.hpp"
#include "fmt/core.h"

#include "LuaManager.hpp"
#include "Map.hpp"
#include "Constants.hpp"
#include "EntityManager.hpp"
#include "Game.hpp"
#include "AssetsManager.hpp"
#include "components/TransformComponent.hpp"
#include "components/SpriteComponent.hpp"
#include "components/KeyboardControlComponent.hpp"
#include "components/MeshComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/ProjectileEmitterComponent.hpp"
#include "components/ParticlesComponent.hpp"

LuaManager::LuaManager() = default;

LuaManager::~LuaManager() = default;

void LuaManager::loadFile(const std::string &filePath_, Entity& player) {
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

    // Level Name
    int idx = filePath_.rfind('/');
    std::string levelName = filePath_.substr(idx + 1);

    // Remove .lua
    idx = levelName.rfind('.');
    int stringSize = levelName.size();

    while ( stringSize > idx ) {
        levelName.pop_back();
        stringSize--;
    }

    lua.script_file(filePath_);

    sol::table levelData = lua[levelName];

    // LOADS MAP FORM LUA CONFIG FILE
    sol::table levelMap = levelData["map"];

    Game::map->loadMap(levelMap["file"],
                 glm::vec2(levelMap["size"]["width"], levelMap["size"]["height"]),
                 levelMap["tileSize"],
                 levelMap["textureID"]);

    // LOADS ENTITIES FORM LUA CONFIG FILE
    sol::table levelEntities = levelData["entities"];
    unsigned int entityIndex = 0;

    while ( true ) {
        sol::optional<sol::table> existsEntityIndexNode = levelEntities[entityIndex];

        if ( existsEntityIndexNode == sol::nullopt ) {
            break;
        } else {
            sol::table entity = levelEntities[entityIndex];
            EntityType entityType = static_cast<EntityType>(static_cast<int>(entity["entityType"]));

            // Add entity
            auto ent = Game::entityManager->addEntity(entityType);

            if ( entityType == PLAYER ) player = ent;

            // Add Transform component
            sol::optional<sol::table> existsTransformComponent = entity["components"]["transform"];

            if ( existsTransformComponent != sol::nullopt ) {
                sol::table transformComponent = entity["components"]["transform"];

                glm::vec2 entityPos = glm::vec2(static_cast<float>(transformComponent["position"]["x"]),
                                                static_cast<float>(transformComponent["position"]["y"]));

                glm::vec2 entitySize = glm::vec2(static_cast<float>(transformComponent["size"]["width"]),
                                                static_cast<float>(transformComponent["size"]["height"]));

                Game::entityManager->registry.emplace<TransformComponent>(ent.entity,
                                                                          entityPos,
                                                                          entitySize,
                                                                          transformComponent["velocity"]);

            }

            // Add Keyboard Component
            if ( ent.type == PLAYER ) {
                Game::entityManager->registry.emplace<KeyboardControlComponent>(ent.entity, ent);
            }

            // Add Sprite Component
            sol::optional<sol::table> existsSpriteComponent = entity["components"]["sprite"];
            glm::vec2 spriteOffset;

            if ( existsSpriteComponent != sol::nullopt ) {
                sol::table spriteComponent = entity["components"]["sprite"];
                bool isAnimated = spriteComponent["isAnimated"];

                if ( isAnimated ) {
                    spriteOffset = glm::vec2(static_cast<float>(spriteComponent["spriteOffset"]["x"]),
                                             static_cast<float>(spriteComponent["spriteOffset"]["y"]));
                } else {
                    spriteOffset = glm::vec2(1.0f, 1.0f);
                }

                Game::entityManager->registry.emplace<SpriteComponent>(ent.entity,
                                                                 ent.id,
                                                                 spriteComponent["textureID"],
                                                                 isAnimated,
                                                                 spriteOffset.x,
                                                                 spriteOffset.y);
            }

            // Add Collision Component
            sol::table transformComponent = entity["components"]["transform"];
            glm::vec2 entityPos = glm::vec2(static_cast<float>(transformComponent["position"]["x"]),
                                            static_cast<float>(transformComponent["position"]["y"]));

            glm::vec2 entitySize = glm::vec2(static_cast<float>(transformComponent["size"]["width"]),
                                             static_cast<float>(transformComponent["size"]["height"]));

            Game::entityManager->registry.emplace<CollisionComponent>(ent.entity,
                                                                b2Vec2{entitySize.x, entitySize.y},
                                                                b2Vec2{entityPos.x, entityPos.y},
                                                                ent.id);

            // Add Mesh Component
            Game::entityManager->registry.emplace<MeshComponent>(ent.entity, std::vector<Vertex>{
                    {glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                     glm::vec2(1.0f / spriteOffset.x, 0.0f) },
                    {glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                     glm::vec2(0.0f, 1.0f / spriteOffset.y) },
                    {glm::vec2(-1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                     glm::vec2(1.0f / spriteOffset.x, 1.0f / spriteOffset.y) },
                    {glm::vec2(1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                     glm::vec2(0.0f, 0.0f) },
            }, std::vector<GLuint> {
                    1, 3, 2,
                    0, 3, 2
            });

            // Add ProjectileEmitterComponent Component
            sol::optional<sol::table> existsProjectileEmitterComponent = entity["components"]["projectileEmitter"];

            if ( existsProjectileEmitterComponent != sol::nullopt ) {
                sol::table projectileComponent = entity["components"]["projectileEmitter"];
                auto projectile = Game::entityManager->addEntity(PROJECTILE);

                glm::vec2 projectileSize = glm::vec2(static_cast<float>(projectileComponent["size"]["width"]),
                                                 static_cast<float>(projectileComponent["size"]["height"]));

                Game::entityManager->registry.emplace<TransformComponent>(projectile.entity,
                                                                          entityPos,
                                                                          projectileSize,
                                                                          static_cast<float>(projectileComponent["speed"]));

                Game::entityManager->registry.emplace<SpriteComponent>(projectile.entity,
                                                                       projectile.id,
                                                                       projectileComponent["textureID"]);

                Game::entityManager->registry.emplace<ProjectileEmitterComponent>(projectile.entity,
                                                                                  ent,
                                                                                  projectile,
                                                                                  projectileComponent["speed"],
                                                                                  projectileComponent["angle"],
                                                                                  projectileComponent["range"],
                                                                                  projectileComponent["shouldLoop"]);

                Game::entityManager->registry.emplace<CollisionComponent>(projectile.entity,
                                                                          b2Vec2(projectileSize.x, projectileSize.y),
                                                                          b2Vec2(entityPos.x, entityPos.y),
                                                                          projectile.id);

                Game::entityManager->registry.emplace<MeshComponent>(projectile.entity, std::vector<Vertex>{
                        {glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                                glm::vec2(1.0f, 0.0f) },
                        {glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                                glm::vec2(0.0f, 1.0f) },
                        {glm::vec2(-1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                                glm::vec2(1.0f, 1.0f) },
                        {glm::vec2(1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                                glm::vec2(0.0f, 0.0f) },
                }, std::vector<GLuint> {
                        1, 3, 2,
                        0, 3, 2
                });

                auto pp = entity["components"]["projectileEmitter"]["particle"];
                ParticleProps particle;
                particle.colorBegin = { pp["colorBegin"]["r"], pp["colorBegin"]["g"],
                                        pp["colorBegin"]["b"], pp["colorBegin"]["a"] };
                particle.colorEnd = { pp["colorEnd"]["r"], pp["colorEnd"]["g"],
                                      pp["colorEnd"]["b"], pp["colorEnd"]["a"] };
                particle.sizeBegin = pp["sizeBegin"];
                particle.sizeVariation = pp["sizeVariation"];
                particle.sizeEnd = pp["sizeEnd"];
                particle.lifeTime = pp["lifeTime"];
                particle.velocity = { pp["velocity"]["x"], pp["velocity"]["y"] };
                particle.velocityVariation = { pp["velocityVariation"]["x"], pp["velocityVariation"]["y"] };
                particle.position = { pp["position"]["x"], pp["position"]["y"] };
                particle.scale =  0.00000001f;

                Game::entityManager->registry.emplace<ParticleComponent>(projectile.entity, projectile, particle);
            }

            entityIndex++;
        }
    }
}
