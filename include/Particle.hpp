#pragma once

#include <glm/glm.hpp>

struct Particle {
    Particle() = default;
    Particle(const glm::vec2 &position, float mass, float radius);
    Particle(const glm::vec2 &position, float mass, float radius, bool pinned);

    glm::vec2 force{0.0f, 0.0f};
    glm::vec2 velocity{0.0f, 0.0f};
    glm::vec2 position{0.0f, 0.0f};
    float mass{0.0f};
    float radius{0.0f};
    bool pinned{false};
};
