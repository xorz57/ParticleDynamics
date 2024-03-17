#pragma once

#include "Particle.hpp"

struct Spring {
    Spring(Particle &particle1, Particle &particle2, float restLength, float springConstant, float dampingConstant);
    Particle &mParticle1;
    Particle &mParticle2;
    float mRestLength{0.0f};
    float mSpringConstant{0.0f};
    float mDampingConstant{0.0f};
};
