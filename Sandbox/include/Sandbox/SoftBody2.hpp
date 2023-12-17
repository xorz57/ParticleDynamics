#pragma once

#include "Engine/SoftBody.hpp"

struct SoftBody2 : Engine::SoftBody {
    SoftBody2(const glm::vec2 &center, float size, float particleMass, float particleRadius);
};
