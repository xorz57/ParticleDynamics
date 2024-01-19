#include "SoftBody3.hpp"

#include <glm/gtc/constants.hpp>

SoftBody3::SoftBody3(const glm::vec2 &center, float radius, float particleMass, float particleRadius, std::size_t numParticles) : SoftBody() {
    const float angleIncrement = 2 * glm::pi<float>() / static_cast<float>(numParticles);

    for (std::size_t i = 0; i < numParticles; i++) {
        const float angle = angleIncrement * static_cast<float>(i);
        const auto position = center + radius * glm::vec2(glm::cos(angle), glm::sin(angle));
        particles.emplace_back(position, particleMass, particleRadius);
    }

    const auto distance = [](const Particle &particle1, const Particle &particle2) {
        const glm::vec2 displacement = particle2.position - particle1.position;
        return glm::length(displacement);
    };

    for (std::size_t i = 0; i < particles.size(); i++) {
        for (std::size_t j = i + 1; j < particles.size(); j++) {
            springs.emplace_back(particles[i], particles[j], distance(particles[i], particles[j]), 100.0f, 2.0f);
        }
    }
}
