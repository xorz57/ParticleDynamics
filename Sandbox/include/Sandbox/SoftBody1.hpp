#pragma once

#include "Engine/SoftBody.hpp"

struct SoftBody1 : Engine::SoftBody {
    SoftBody1(const glm::vec2 &centroid, float size, float particleMass, float particleRadius);
};
