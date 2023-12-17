#include "Sandbox/SoftBody2.hpp"

SoftBody2::SoftBody2(const glm::vec2 &center, float size, float particleMass, float particleRadius) : SoftBody() {
    particles.emplace_back(center + glm::vec2(-size, -size), particleMass, particleRadius);
    particles.emplace_back(center + glm::vec2(+size, -size), particleMass, particleRadius);
    particles.emplace_back(center + glm::vec2(+size, +size), particleMass, particleRadius);
    particles.emplace_back(center + glm::vec2(-size, +size), particleMass, particleRadius);

    const auto distance = [](const Engine::Particle &particle1, const Engine::Particle &particle2) {
        const glm::vec2 displacement = particle2.position - particle1.position;
        return glm::length(displacement);
    };

    springs.emplace_back(particles[0], particles[1], distance(particles[0], particles[1]), 100.0f, 2.0f);
    springs.emplace_back(particles[1], particles[2], distance(particles[1], particles[2]), 100.0f, 2.0f);
    springs.emplace_back(particles[2], particles[3], distance(particles[2], particles[3]), 100.0f, 2.0f);
    springs.emplace_back(particles[3], particles[0], distance(particles[3], particles[0]), 100.0f, 2.0f);

    springs.emplace_back(particles[0], particles[2], distance(particles[0], particles[2]), 100.0f, 2.0f);
    springs.emplace_back(particles[1], particles[3], distance(particles[1], particles[3]), 100.0f, 2.0f);
}
