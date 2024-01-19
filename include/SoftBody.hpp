#pragma once

#include "Particle.hpp"
#include "Spring.hpp"

#include <vector>

struct SoftBody {
    std::vector<Particle> particles;
    std::vector<Spring> springs;
};
