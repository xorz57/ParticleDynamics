#pragma once

#include "SoftBody.hpp"

struct Cloth : SoftBody {
    Cloth(const glm::vec2 &position, unsigned int rows, unsigned int cols, float padding);

    float particleMass{1.0f};
    float particleRadius{1.0f};
    float springConstant{100.0f};
    float dampingConstant{2.0f};
};
