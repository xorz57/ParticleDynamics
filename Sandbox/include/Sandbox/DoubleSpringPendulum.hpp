#pragma once

#include "Engine/SoftBody.hpp"

struct DoubleSpringPendulum : Engine::SoftBody {
    DoubleSpringPendulum(const glm::vec2 &pivot, float length, float particleMass, float particleRadius);
};
