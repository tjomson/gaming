#pragma once

#include "Particle.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/random.hpp"
#include <vector>
#include <functional>
#include <sre/Sprite.hpp>
#include <sre/Material.hpp>
#include <sre/RenderPass.hpp>
#include <sre/Mesh.hpp>

class ParticleSystem {
public:
    ParticleSystem(int particleCount, std::shared_ptr<sre::Texture> texture);
    void update(float deltaTime);

    void draw(sre::RenderPass& pr, glm::mat4 transform = glm::mat4(1));

    void emit();                    // explicit emit a particle

    float emissionRate = 60;        // particles per second
    float lifeSpan = 10;            // lifetime for each particle

    bool running = true;
    bool visible = true;
    bool emitting = true;

    glm::vec3 gravity = glm::vec3(0,-9.8,0);

    std::shared_ptr<sre::Material> material;

    std::function<void(Particle&)> emitter; // responsible for setting initial size, position, velocity, rotation and angular velocity

    std::function<void(Particle&)> updateAppearance;              // responsible for updating the color,uv,size (based on particle.normalizedAge)
    std::function<void(Particle&, float)> updatePhysics;          // responsible for updating the position and rotation based on deltaTime

    int getActiveParticles();
private:
    int activeParticles = 0;
    float time = 0;
    float emissions = 0;
    int particleIndex = 0;
    std::vector<Particle> particles;
    std::shared_ptr<sre::Texture> texture;
    std::shared_ptr<sre::Mesh> mesh;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec4> colors;
    std::vector<float> sizes;
    std::vector<glm::vec4> uvs;
};




