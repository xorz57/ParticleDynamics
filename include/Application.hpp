#pragma once

#include "SoftBody.hpp"

#include <SFML/System/Time.hpp>

class Application {
public:
    Application();
    void FixedUpdate(const sf::Time &fixedDeltaTime);
    void Run();

private:
    glm::vec2 mGravitationalAcceleration{0.0f, 10.0f};
    std::vector<SoftBody> mSoftBodies;
};
