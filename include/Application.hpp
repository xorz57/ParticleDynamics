#pragma once

#include "SoftBody.hpp"

#include <SFML/System/String.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

class Application {
public:
    Application();
    void FixedUpdate(const sf::Time &fixedDeltaTime);
    void Run();

private:
    sf::VideoMode mMode{600u, 600u};
    sf::String mTitle{"ParticlePhysics"};
    sf::Uint32 mStyle{sf::Style::Default};
    sf::ContextSettings mSettings{24u, 8u, 8u, 3u, 3u};
    glm::vec2 mGravitationalAcceleration{0.0f, 10.0f};
    std::vector<SoftBody> mSoftBodies;
};
