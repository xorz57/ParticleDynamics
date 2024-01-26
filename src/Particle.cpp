#include "Particle.hpp"

#include <glm/gtc/constants.hpp>

Particle::Particle(const glm::vec2 &position, float mass, float radius) : position(position),
                                                                          mass(mass),
                                                                          radius(radius) {}

Particle::Particle(const glm::vec2 &position, float mass, float radius, bool pinned) : position(position),
                                                                                       mass(mass),
                                                                                       radius(radius),
                                                                                       pinned(pinned) {}
