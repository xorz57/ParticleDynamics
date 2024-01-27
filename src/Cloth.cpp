#include "Cloth.hpp"

Cloth::Cloth(const glm::vec2 &position, unsigned int rows, unsigned int cols, float padding) : SoftBody() {
    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int col = 0; col < cols; ++col) {
            const bool pinned = (row == 0) ? true : false;
            particles.emplace_back(position + padding * glm::vec2(col, row), 2.0f, 4.0f, pinned);
        }
    }

    const auto distance = [](const Particle &particle1, const Particle &particle2) {
        const glm::vec2 displacement = particle2.position - particle1.position;
        return glm::length(displacement);
    };

    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int col = 0; col < cols; ++col) {
            if (col < cols - 1) {
                Particle &particle1 = particles[row * cols + col];
                Particle &particle2 = particles[row * cols + col + 1];
                springs.emplace_back(particle1, particle2, distance(particle1, particle2), 32.0f, 1.0f);
            }
            if (row < rows - 1) {
                Particle &particle1 = particles[row * cols + col];
                Particle &particle2 = particles[(row + 1) * cols + col];
                springs.emplace_back(particle1, particle2, distance(particle1, particle2), 32.0f, 1.0f);
            }
        }
    }
}
