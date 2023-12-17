#include "Engine/Spring.hpp"

using namespace Engine;

Spring::Spring(Particle &particle1, Particle &particle2, float restLength, float springConstant, float dampingConstant)
    : mParticle1(particle1),
      mParticle2(particle2),
      mRestLength(restLength),
      mSpringConstant(springConstant),
      mDampingConstant(dampingConstant) {}
