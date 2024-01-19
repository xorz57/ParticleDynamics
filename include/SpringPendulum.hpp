#pragma once

#include "SoftBody.hpp"

struct SpringPendulum : SoftBody {
    SpringPendulum(const glm::vec2 &pivot, float length, float particleMass, float particleRadius);
};
