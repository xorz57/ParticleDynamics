#pragma once

#include "SoftBody.hpp"

struct SoftBody2 : SoftBody {
    SoftBody2(const glm::vec2 &center, float size, float particleMass, float particleRadius);
};
