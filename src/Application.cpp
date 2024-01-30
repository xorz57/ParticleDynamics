#include "Application.hpp"
#include "Cloth.hpp"
#include "Particle.hpp"
#include "Spring.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui-SFML.h>
#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

Application::Application() {
    mWindow.create(mMode, mTitle, mStyle, mSettings);
    mWindow.setFramerateLimit(60u);
    mView = mWindow.getDefaultView();
}

void Application::Run() {
    const unsigned int rows = 32u;
    const unsigned int cols = 32u;
    const float padding = 8.0f;
    const glm::vec2 position = 0.5f * glm::vec2(mMode.width, mMode.height) - 0.5f * padding * glm::vec2(cols - 1, rows - 1);
    mSoftBodies.emplace_back(Cloth(position, rows, cols, padding));

    (void) ImGui::SFML::Init(mWindow);

    const sf::Time fixedDeltaTime = sf::seconds(1.0f / 128.0f);
    float timeScale = 5.0f;
    sf::Time accumulator = sf::Time::Zero;
    sf::Clock deltaClock;
    while (mWindow.isOpen()) {
        ProcessEvents();

        const sf::Time deltaTime = deltaClock.restart();
        const sf::Time scaledDeltaTime = timeScale * deltaTime;

        accumulator += scaledDeltaTime;
        while (accumulator > fixedDeltaTime) {
            FixedUpdate(fixedDeltaTime);
            accumulator -= fixedDeltaTime;
        }

        if (mIsSoftBodySelected && mIsParticleSelected) {
            const sf::Vector2i pixelPosition = sf::Mouse::getPosition(mWindow);
            const sf::Vector2f worldPosition = mWindow.mapPixelToCoords(pixelPosition);
            Particle &selectedParticle = mSoftBodies[mSelectedSoftBodyIndex].particles[mSelectedParticleIndex];
            selectedParticle.force = glm::vec2(0.0f, 0.0f);
            selectedParticle.velocity = glm::vec2(0.0f, 0.0f);
            selectedParticle.position = glm::vec2(worldPosition.x, worldPosition.y);
        }

        ImGui::SFML::Update(mWindow, deltaTime);

        ImGui::Begin("Settings");
        ImGui::DragFloat("Time Scale", &timeScale, 0.1f, 0.0f, 10.0f);
        ImGui::DragFloat2("Gravity", glm::value_ptr(mGravitationalAcceleration), 0.1f, -9.8f, 9.8f);
        ImGui::End();

        ImGui::Begin("Statistics");
        ImGui::Text("FPS               : %3.f", 1.0f / deltaTime.asSeconds());
        ImGui::Text("Tick Rate         : %3.f", 1.0f / fixedDeltaTime.asSeconds());
        ImGui::Text("Fixed Delta Time  : %3d ms", fixedDeltaTime.asMilliseconds());
        ImGui::Text("Delta Time        : %3d ms", deltaTime.asMilliseconds());
        ImGui::Text("Scaled Delta Time : %3d ms", scaledDeltaTime.asMilliseconds());
        ImGui::End();

        mWindow.clear(sf::Color(25, 25, 25));

        for (const SoftBody &softBody: mSoftBodies) {
            sf::VertexArray clothSurface(sf::Triangles);
            for (unsigned int i = 0; i < rows - 1; ++i) {
                for (unsigned int j = 0; j < cols - 1; ++j) {
                    const unsigned int index1 = i * cols + j;
                    const unsigned int index2 = (i + 1) * cols + j;
                    const unsigned int index3 = i * cols + (j + 1);
                    const unsigned int index4 = (i + 1) * cols + (j + 1);
                    const sf::Color color(80u, 80u, 80u);
                    clothSurface.append(sf::Vertex(sf::Vector2f(softBody.particles[index1].position.x, softBody.particles[index1].position.y), color));
                    clothSurface.append(sf::Vertex(sf::Vector2f(softBody.particles[index2].position.x, softBody.particles[index2].position.y), color));
                    clothSurface.append(sf::Vertex(sf::Vector2f(softBody.particles[index3].position.x, softBody.particles[index3].position.y), color));
                    clothSurface.append(sf::Vertex(sf::Vector2f(softBody.particles[index2].position.x, softBody.particles[index2].position.y), color));
                    clothSurface.append(sf::Vertex(sf::Vector2f(softBody.particles[index4].position.x, softBody.particles[index4].position.y), color));
                    clothSurface.append(sf::Vertex(sf::Vector2f(softBody.particles[index3].position.x, softBody.particles[index3].position.y), color));
                }
            }
            mWindow.draw(clothSurface);
        }

        for (const SoftBody &softBody: mSoftBodies) {
            for (const Spring &spring: softBody.springs) {
                sf::VertexArray line(sf::Lines, 2);
                line[0].position.x = spring.mParticle1.position.x;
                line[1].position.x = spring.mParticle2.position.x;
                line[0].position.y = spring.mParticle1.position.y;
                line[1].position.y = spring.mParticle2.position.y;
                line[0].color = sf::Color(150, 150, 150);
                line[1].color = sf::Color(150, 150, 150);
                mWindow.draw(line);
            }
            for (const Particle &particle: softBody.particles) {
                sf::CircleShape shape;
                shape.setRadius(particle.radius);
                shape.setOrigin(particle.radius, particle.radius);
                shape.setPosition(particle.position.x, particle.position.y);
                Particle &selectedParticle = mSoftBodies[mSelectedSoftBodyIndex].particles[mSelectedParticleIndex];
                if (mIsSoftBodySelected && mIsParticleSelected && &particle == &selectedParticle) {
                    shape.setFillColor(sf::Color(200, 0, 0));
                } else {
                    shape.setFillColor(sf::Color(200, 200, 200));
                }
                mWindow.draw(shape);
            }
        }

        ImGui::SFML::Render(mWindow);

        mWindow.display();
    }

    ImGui::SFML::Shutdown();
}

void Application::ProcessEvents() {
    sf::Event event{};
    while (mWindow.pollEvent(event)) {
        ImGui::SFML::ProcessEvent(mWindow, event);
        switch (event.type) {
            case sf::Event::Closed:
                HandleEventClosed(event);
                break;

            case sf::Event::Resized:
                HandleEventResized(event);
                break;

            case sf::Event::MouseWheelScrolled:
                HandleEventMouseWheelScrolled(event);
                break;

            case sf::Event::MouseButtonPressed:
                HandleEventMouseButtonPressed(event);
                break;

            case sf::Event::MouseButtonReleased:
                HandleEventMouseButtonReleased(event);
                break;

            default:
                break;
        }
    }
}

void Application::HandleEventClosed(const sf::Event &event) {
    mWindow.close();
}

void Application::HandleEventResized(const sf::Event &event) {
    mView.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
    mWindow.setView(mView);
}

void Application::HandleEventMouseWheelScrolled(const sf::Event &event) {
    if (event.mouseWheelScroll.delta > 0.0f) {
        mView.zoom(1.0f / 1.05f);
    }
    if (event.mouseWheelScroll.delta < 0.0f) {
        mView.zoom(1.05f);
    }
    mWindow.setView(mView);
}

void Application::HandleEventMouseButtonPressed(const sf::Event &event) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        for (size_t softBodyIndex = 0; softBodyIndex < mSoftBodies.size(); ++softBodyIndex) {
            const SoftBody &softBody = mSoftBodies[softBodyIndex];
            for (size_t particleIndex = 0; particleIndex < softBody.particles.size(); ++particleIndex) {
                const Particle &particle = softBody.particles[particleIndex];
                const sf::Vector2i pixelPosition = sf::Mouse::getPosition(mWindow);
                const sf::Vector2f worldPosition = mWindow.mapPixelToCoords(pixelPosition);
                const float distance = glm::length(glm::vec2(worldPosition.x - particle.position.x, worldPosition.y - particle.position.y));
                if (distance <= particle.radius) {
                    mIsSoftBodySelected = true;
                    mIsParticleSelected = true;
                    mSelectedSoftBodyIndex = softBodyIndex;
                    mSelectedParticleIndex = particleIndex;
                    break;
                }
            }
        }
    }
}

void Application::HandleEventMouseButtonReleased(const sf::Event &event) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        mIsSoftBodySelected = false;
        mIsParticleSelected = false;
    }
}

void Application::FixedUpdate(const sf::Time &fixedDeltaTime) {
    const float dt = fixedDeltaTime.asSeconds();
    for (SoftBody &softBody: mSoftBodies) {
        for (Spring &spring: softBody.springs) {
            const glm::vec2 dPosition = spring.mParticle2.position - spring.mParticle1.position;
            const glm::vec2 dVelocity = spring.mParticle2.velocity - spring.mParticle1.velocity;
            if (glm::length(dPosition) != 0) {
                const glm::vec2 springForce = spring.mSpringConstant * (glm::length(dPosition) - spring.mRestLength) * glm::normalize(dPosition);
                const glm::vec2 dampingForce = spring.mDampingConstant * dVelocity;
                const glm::vec2 force = springForce + dampingForce;
                spring.mParticle1.force += force;
                spring.mParticle2.force -= force;
            }
        }
        for (Particle &particle: softBody.particles) {
            const glm::vec2 gravitationalForce = particle.mass * mGravitationalAcceleration;
            particle.force += gravitationalForce;
            if (!particle.pinned) {
                const glm::vec2 acceleration = particle.force * (1.0f / particle.mass);
                particle.velocity += acceleration * dt;
                particle.position += particle.velocity * dt;
            }
            particle.force = glm::vec2(0.0f, 0.0f);
        }
    }
}
