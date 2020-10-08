#include <utility>
#include <random>

#include "ParticleEmitter.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "EntityManager.hpp"
#include "Game.hpp"
#include "components/TransformComponent.hpp"

ParticleEmitter::ParticleEmitter(Shader &shader, std::shared_ptr<Texture> texture, unsigned int amount)
        : shader(shader), texture(std::move(texture)), amount(amount) {
    init();
}

void ParticleEmitter::Update(float dt_, Entity entity_, unsigned int newParticles_, glm::vec2 offset_) {
    for ( unsigned int i = 0; i < newParticles_; i++ ) {
        int unusedParticle = static_cast<int>(firstUnusedParticle());
        respawnParticle(particles[unusedParticle], entity_, offset_);
    }

    for ( auto& particle : particles ) {
        particle.life -= dt_;

        if ( particle.life > 0.0f ) {
            particle.position -= particle.velocity * dt_;
            particle.color.a -= dt_ * 2.5f;
        }
    }
}

void ParticleEmitter::Draw() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    shader.useShader();

    for ( Particle particle : particles ) {
        if ( particle.life > 0.0f ) {
            glUniform2f(shader.getUniformLocation("offset"), particle.position.x, particle.position.y);

            glUniform4f(shader.getUniformLocation("color"), particle.color.x, particle.color.y,
                        particle.color.z, particle.color.w);

            texture->useTexture();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleEmitter::init() {
    unsigned int VBO[2];
    std::vector<glm::vec2> particlePosition {
            glm::vec2(0.0f, 1.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(0.0f, 0.0f),
            glm::vec2(0.0f, 1.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(1.0f, 0.0f),
    };

    std::vector<glm::vec2> particleTextureCords {
            glm::vec2(0.0f, 1.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(0.0f, 0.0f),
            glm::vec2(0.0f, 1.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(1.0f, 0.0f),
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(2, VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particlePosition[0]) * particlePosition.size(), &particlePosition[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(particlePosition[0]), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particleTextureCords[0]) * particleTextureCords.size(), &particleTextureCords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(particleTextureCords[0]), nullptr);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    for ( unsigned int i = 0; i < this->amount; i++ ) particles.emplace_back(Particle());
}

unsigned int lastUsedParticle = 0;
unsigned int ParticleEmitter::firstUnusedParticle() {
    for ( unsigned int i = lastUsedParticle; i < this->amount; i++ ){
        if ( particles[i].life <= 0.0f ) {
            lastUsedParticle = i;
            return i;
        }
    }

    for ( unsigned int i = 0; i < lastUsedParticle; i++ ){
        if ( particles[i].life <= 0.0f ) {
            lastUsedParticle = i;
            return i;
        }
    }

    lastUsedParticle = 0;
    return 0;
}

void ParticleEmitter::respawnParticle(Particle &particle_, Entity entity_, glm::vec2 offset_) {
    auto& tc = Game::entityManager->registry.get<TransformComponent>(entity_.entity);

    std::random_device generator;
    std::uniform_int_distribution<int> distribution(1, 50);

    float random = (static_cast<float>(distribution(generator)) - 50) / 10.0f;
    float rColor = 0.5f + (static_cast<float>(distribution(generator)) / 100.0f);
    particle_.position = tc.position + random + offset_;
    particle_.color = glm::vec4(rColor, rColor, rColor, 1.0f);
    particle_.life = 1.0f;
    particle_.velocity = tc.velocity * 0.1f;

    fmt::print("random: {}\n", random);
    fmt::print("Particle position: {}, {}\n", particle_.position.x, particle_.position.y);
    fmt::print("Offset: {}, {}\n", offset_.x, offset_.y);

}
