#pragma once

#include "SoftBody.hpp"

struct SoftBody3 : SoftBody {
    SoftBody3(const glm::vec2 &center, float radius, float particleMass, float particleRadius, std::size_t numParticles);
};
