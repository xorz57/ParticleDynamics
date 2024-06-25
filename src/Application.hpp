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

    void run();

private:
    void processEvents();
    void handleEventClosed(const sf::Event &event);
    void handleEventResized(const sf::Event &event);
    void handleEventMouseWheelScrolled(const sf::Event &event);
    void handleEventMouseButtonPressed(const sf::Event &event);
    void handleEventMouseButtonReleased(const sf::Event &event);
    void fixedUpdate(const sf::Time &fixedDeltaTime);

    sf::VideoMode mMode{800u, 600u};
    sf::String mTitle{"Particle Physics"};
    sf::Uint32 mStyle{sf::Style::Default};
    sf::ContextSettings mSettings{24u, 8u, 8u, 3u, 3u};
    sf::RenderWindow mWindow;
    sf::View mView;
    std::vector<SoftBody> mSoftBodies;
    glm::vec2 mGravitationalAcceleration{0.0f, 9.8f};
    bool mIsSoftBodySelected{false};
    bool mIsParticleSelected{false};
    size_t mSelectedSoftBodyIndex{0};
    size_t mSelectedParticleIndex{0};
};
