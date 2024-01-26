#pragma once

#include "SoftBody.hpp"

struct Cloth : SoftBody {
    Cloth(const glm::vec2 &position, unsigned int rows, unsigned int cols, float padding);
};
