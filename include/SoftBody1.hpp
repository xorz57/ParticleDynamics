#pragma once

#include "SoftBody.hpp"

struct SoftBody1 : SoftBody {
    SoftBody1(const glm::vec2 &centroid, float size, float particleMass, float particleRadius);
};
