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
    void Run();

private:
    void ProcessEvents();
    void HandleEventClosed(const sf::Event &event);
    void HandleEventResized(const sf::Event &event);
    void HandleEventMouseWheelScrolled(const sf::Event &event);
    void HandleEventMouseButtonPressed(const sf::Event &event);
    void HandleEventMouseButtonReleased(const sf::Event &event);
    void FixedUpdate(const sf::Time &fixedDeltaTime);

    sf::VideoMode mMode{800u, 600u};
    sf::String mTitle{"ParticlePhysics"};
    sf::Uint32 mStyle{sf::Style::Default};
    sf::ContextSettings mSettings{24u, 8u, 8u, 3u, 3u};
    sf::RenderWindow mWindow;
    sf::View mView;
    glm::vec2 mGravitationalAcceleration{0.0f, 9.8f};
    std::vector<SoftBody> mSoftBodies;
    bool mIsSoftBodySelected{false};
    bool mIsParticleSelected{false};
    size_t mSelectedSoftBodyIndex{0};
    size_t mSelectedParticleIndex{0};
};
