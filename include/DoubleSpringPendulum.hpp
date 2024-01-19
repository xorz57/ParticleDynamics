#pragma once

#include "SoftBody.hpp"

struct DoubleSpringPendulum : SoftBody {
    DoubleSpringPendulum(const glm::vec2 &pivot, float length, float particleMass, float particleRadius);
};
