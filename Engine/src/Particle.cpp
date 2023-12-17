#include "Engine/Particle.hpp"

#include <glm/gtc/constants.hpp>

using namespace Engine;

Particle::Particle(const glm::vec2 &position, float mass, float radius) : position(position),
                                                                          mass(mass),
                                                                          radius(radius) {}

Particle::Particle(const glm::vec2 &position, float mass, float radius, bool pinned) : position(position),
                                                                                       mass(mass),
                                                                                       radius(radius),
                                                                                       pinned(pinned) {}

void Particle::HandleBoundaryCollisions() {
    const float dampingFactor = 0.001f;
    const glm::vec2 boundarySize(600.0f, 600.0f);

    if (position.x >= boundarySize.x - radius || position.x <= radius) {
        position.x = glm::clamp(position.x, radius, boundarySize.x - radius);
        velocity.x = -velocity.x * (1.0f - dampingFactor);
    }

    if (position.y >= boundarySize.y - radius || position.y <= radius) {
        position.y = glm::clamp(position.y, radius, boundarySize.y - radius);
        velocity.y = -velocity.y * (1.0f - dampingFactor);
    }
}
