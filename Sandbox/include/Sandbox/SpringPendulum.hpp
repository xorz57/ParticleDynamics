#pragma once

#include "Engine/SoftBody.hpp"

struct SpringPendulum : Engine::SoftBody {
    SpringPendulum(const glm::vec2 &pivot, float length, float particleMass, float particleRadius);
};
