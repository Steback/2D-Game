#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/compatibility.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "fmt/core.h"

#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Shader.hpp"

ParticleSystem::ParticleSystem() {
    m_particlePool.resize(1000);
}

ParticleSystem::~ParticleSystem() {
    if ( m_quadVA != 0 ) {
        glDeleteBuffers(1, &m_quadVA);
        m_quadVA = 0;
    }
}

void ParticleSystem::onUpdate(float dt) {
    for (auto& particle : m_particlePool) {
        if (!particle.active) {
            continue;
        }

        if (particle.lifeRemaining <= 0.0f) {
            particle.active = false;
            continue;
        }

        particle.lifeRemaining -= dt;
        particle.position += particle.velocity * dt;
        particle.rotation += 0.01f * dt;
    }
}

void ParticleSystem::onRender(const glm::mat4& view, const glm::mat4& proj) {
    if (!m_quadVA) {
        float vertices[] = {
                -0.5f, -0.5f,
                0.5f, -0.5f,
                0.5f,  0.5f,
                -0.5f,  0.5f,
        };

        glGenVertexArrays(1, &m_quadVA);
        glBindVertexArray(m_quadVA);

        GLuint quadVB, quadIB;
        glGenBuffers(1, &quadVB);
        glBindBuffer(GL_ARRAY_BUFFER, quadVB);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        uint32_t indices[] = {
                0, 1, 2, 2, 3, 0
        };

        glGenBuffers(1, &quadIB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        m_particleShader = std::make_unique<Shader>("assets/shaders/particle.vert", "assets/shaders/particle.frag");
        m_particleShaderView = m_particleShader->getUniformLocation("u_view");
        m_particleShaderProj = m_particleShader->getUniformLocation("u_projection");
        m_particleShaderModel = m_particleShader->getUniformLocation("u_model");
        m_particleShaderColor = m_particleShader->getUniformLocation("u_color");
    }

    m_particleShader->useShader();
    glUniformMatrix4fv(m_particleShaderView, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(m_particleShaderProj, 1, GL_FALSE, glm::value_ptr(proj));

    for (auto& particle : m_particlePool) {
        if (!particle.active)
            continue;

        // Fade away particles
        float life = particle.lifeRemaining / particle.lifeTime;
        glm::vec4 color = glm::lerp(particle.colorEnd, particle.colorBegin, life);
        //color.a = color.a * life;

        float size = glm::lerp(particle.sizeEnd, particle.sizeBegin, life);


        // Render
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, { particle.position.x, particle.position.y, 0.0f });
        model = glm::rotate(model, particle.rotation, { 0.0f, 0.0f, 1.0f });
        model = glm::scale(model, { size, size, 1.0f });

        glUniformMatrix4fv(m_particleShaderModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform4fv(m_particleShaderColor, 1, glm::value_ptr(color));

        glBindVertexArray(m_quadVA);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}

void ParticleSystem::emit(const ParticleProps &particleProps) {
    Particle& particle = m_particlePool[m_poolIndex];
    particle.active = true;
    particle.position = particleProps.position;
    particle.rotation = Random::Float() * 2.0f * glm::pi<float>();

    // Velocity
    particle.velocity = particleProps.velocity;
    particle.velocity.x += particleProps.velocityVariation.x * ((Random::Float() - 0.5f) * particleProps.scale);
    particle.velocity.y += particleProps.velocityVariation.y * ((Random::Float() - 0.5f) * particleProps.scale);

    // Color
    particle.colorBegin = particleProps.colorBegin;
    particle.colorEnd = particleProps.colorEnd;

    particle.lifeTime = particleProps.lifeTime;
    particle.lifeRemaining = particleProps.lifeTime;

    particle.sizeBegin = particleProps.sizeBegin + particleProps.sizeVariation
            * ((Random::Float() - 0.5f) * particleProps.scale);
    particle.sizeEnd = particleProps.sizeEnd;

    m_poolIndex = --m_poolIndex % m_particlePool.size();
}
