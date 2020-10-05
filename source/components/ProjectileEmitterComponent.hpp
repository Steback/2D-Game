#ifndef PROJECTILE_EMITTER_COMPONENT_HPP
#define PROJECTILE_EMITTER_COMPONENT_HPP

#include "glm/glm.hpp"

#include "TransformComponent.hpp"
#include "../EntityManager.hpp"
#include "../Game.hpp"

class ProjectileEmitterComponent {
    public:
        Entity owner;
        Entity projectile;
        float speed;
        float angleRad;
        float range;
        bool shouldLoop;
        glm::vec2 origin;

    ProjectileEmitterComponent(Entity owner_, Entity projectile_,
                               float speed, float angleDeg, float range, bool shouldLoop = false)
                                : owner(owner_), projectile(projectile_), speed(speed),
                                  angleRad(glm::radians(angleDeg)), range(range), shouldLoop(shouldLoop) {
        origin = Game::entityManager->registry.get<TransformComponent>(owner.entity).position;
        Game::entityManager->registry.get<TransformComponent>(projectile.entity).velocity =
                glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed);
    }

    ~ProjectileEmitterComponent() = default;

    void update(float deltaTime_) const {
        auto& tc = Game::entityManager->registry.get<TransformComponent>(projectile.entity);
        if ( glm::distance(tc.position, origin) > range ) {
            if ( shouldLoop ) {
                tc.position = origin;
            } else {
                Game::entityManager->registry.destroy(projectile.entity);
            }
        } else {
            tc.position.x += tc.velocity.x * deltaTime_;
            tc.position.y += tc.velocity.y * deltaTime_;
        }
    }
};

#endif
