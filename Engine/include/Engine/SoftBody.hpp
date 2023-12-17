#pragma once

#include "Engine/Particle.hpp"
#include "Engine/Spring.hpp"

#include <vector>

namespace Engine {
    struct SoftBody {
        std::vector<Engine::Particle> particles;
        std::vector<Engine::Spring> springs;
    };
}// namespace Engine
