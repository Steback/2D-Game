#ifndef PARTICLE_SYSTEM_HPP
#define PARTICLE_SYSTEM_HPP


#include <vector>
#include <memory>

#include "glm/glm.hpp"

#include "Shader.hpp"

class Shader;

struct ParticleProps {
    glm::vec2 position;
    glm::vec2 velocity, velocityVariation;
    glm::vec4 colorBegin, colorEnd;
    float sizeBegin, sizeEnd, sizeVariation;
    float lifeTime = 1.0f;
    float scale;
};

class ParticleSystem {
    public:
        ParticleSystem();

        void onUpdate(float dt);
        void onRender(const glm::mat4& view, const glm::mat4& proj);

        void emit(const ParticleProps& particleProps);

    private:
        struct Particle {
            glm::vec2 position;
            glm::vec2 velocity;
            glm::vec4 colorBegin, colorEnd;
            float rotation = 0.0f;
            float sizeBegin, sizeEnd;

            float lifeTime = 1.0f;
            float lifeRemaining = 0.0f;

            bool active = false;
        };

        std::vector<Particle> m_particlePool;
        uint32_t m_poolIndex = 999;

        GLuint m_quadVA = 0;
        std::unique_ptr<Shader> m_particleShader;
        GLint m_particleShaderView{}, m_particleShaderProj{}, m_particleShaderModel{}, m_particleShaderColor{};
};


#endif
