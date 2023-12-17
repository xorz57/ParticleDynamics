#include "Sandbox/SpringPendulum.hpp"

#include <glm/gtc/constants.hpp>

SpringPendulum::SpringPendulum(const glm::vec2 &pivot, float length, float particleMass, float particleRadius) : SoftBody() {
    particles.emplace_back(pivot, particleMass, particleRadius, true);

    constexpr float angle = glm::pi<float>() / 4.0f;
    const glm::vec2 position = pivot + length * glm::vec2(glm::cos(angle), glm::sin(angle));
    particles.emplace_back(position, particleMass, particleRadius, false);

    const auto distance = [](const Engine::Particle &particle1, const Engine::Particle &particle2) {
        const glm::vec2 displacement = particle2.position - particle1.position;
        return glm::length(displacement);
    };

    springs.emplace_back(particles[0], particles[1], distance(particles[0], particles[1]), 10.0f, 0.2f);
}
