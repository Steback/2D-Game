#ifndef PARTICLE_EMITTER_HPP
#define PARTICLE_EMITTER_HPP

#include <memory>
#include <vector>

#include "glm/glm.hpp"

class Shader;
class Texture;

struct Entity;

struct Particle {
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec4 color;
    float     life;

    Particle() : position(0.0f), velocity(0.0f), color(1.0f), life(0.0f) { }
};

class ParticleEmitter {
    public:
        ParticleEmitter(Shader &shader, std::shared_ptr<Texture> texture, unsigned int amount);
        void Update(float dt_, Entity entity_, unsigned int newParticles_, glm::vec2 offset_ = glm::vec2(0.0f, 0.0f));
        void Draw(glm::mat4 projection_);

    private:
        Shader& shader;
        std::shared_ptr<Texture> texture;
        unsigned int amount;
        std::vector<Particle> particles;
        unsigned int VAO{};

        void init();
        unsigned int firstUnusedParticle();
        void respawnParticle(Particle &particle_, Entity entity_, glm::vec2 offset_ = glm::vec2(0.0f, 0.0f));
};

#endif
