#ifndef PARTICLES_COMPONENT_HPP
#define PARTICLES_COMPONENT_HPP

#include "../ParticleSystem.hpp"
#include "../EntityManager.hpp"
#include "../Game.hpp"
#include "TransformComponent.hpp"

class ParticleComponent {
    public:
        ParticleComponent(const Entity owner, const ParticleProps &particleProps)
            : m_owner(owner), m_particle(particleProps), particleEmitter(std::make_unique<ParticleSystem>()) {  }

        void update(float deltaTime) {
            auto& ownerTransform = Game::entityManager->registry.get<TransformComponent>(m_owner.entity);

            m_particle.position = ownerTransform.position;

            for (int i = 0; i < 5; i++) {
                particleEmitter->emit(m_particle);
            }

            particleEmitter->onUpdate(deltaTime);
        }

        void render(const glm::mat4& proj, const glm::mat4& view) const {
            particleEmitter->onRender(view, proj);
        }

    public:
        ParticleProps m_particle;
        Entity m_owner;
        std::unique_ptr<ParticleSystem> particleEmitter;
};

#endif
