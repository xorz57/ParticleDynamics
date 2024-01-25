#pragma once

#include "SoftBody.hpp"

class Application {
public:
    Application();
    void FixedUpdate(float fixedDeltaTime);
    void Run();

private:
    glm::vec2 mGravitationalAcceleration{0.0f, 10.0f};
    std::vector<SoftBody> mSoftBodies;
};
