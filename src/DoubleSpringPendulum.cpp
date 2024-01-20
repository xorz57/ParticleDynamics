#include "DoubleSpringPendulum.hpp"

#include <glm/gtc/constants.hpp>

DoubleSpringPendulum::DoubleSpringPendulum(const glm::vec2 &pivot, float length, float particleMass, float particleRadius) : SoftBody() {
    constexpr float angle1 = glm::pi<float>() / 3.0f;
    constexpr float angle2 = glm::pi<float>() / 6.0f;

    const glm::vec2 position1 = pivot + length * glm::vec2(glm::cos(angle1), glm::sin(angle1));
    const glm::vec2 position2 = position1 + length * glm::vec2(glm::cos(angle2), glm::sin(angle2));

    particles.emplace_back(pivot, particleMass, particleRadius, true);
    particles.emplace_back(position1, particleMass, particleRadius, false);
    particles.emplace_back(position2, particleMass, particleRadius, false);

    const auto distance = [](const Particle &particle1, const Particle &particle2) {
        const glm::vec2 displacement = particle2.position - particle1.position;
        return glm::length(displacement);
    };

    springs.emplace_back(particles[0], particles[1], distance(particles[0], particles[1]), 10.0f, 0.2f);
    springs.emplace_back(particles[1], particles[2], distance(particles[1], particles[2]), 10.0f, 0.2f);
}
