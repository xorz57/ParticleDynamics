#pragma once

#include "SoftBody.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
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
    sf::VideoMode mMode{800u, 600u};
    sf::String mTitle{"ParticlePhysics"};
    sf::Uint32 mStyle{sf::Style::Default};
    sf::ContextSettings mSettings{24u, 8u, 8u, 3u, 3u};
    sf::RenderWindow mWindow{mMode, mTitle, mStyle, mSettings};
    sf::View view{mWindow.getDefaultView()};
    glm::vec2 mGravitationalAcceleration{0.0f, 9.8f};
    std::vector<SoftBody> mSoftBodies;
    bool mGrabbedSoftBody{false};
    bool mGrabbedParticle{false};
    size_t mGrabbedSoftBodyIndex{0};
    size_t mGrabbedParticleIndex{0};
};
