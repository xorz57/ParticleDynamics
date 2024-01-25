#include "Application.hpp"
#include "DoubleSpringPendulum.hpp"
#include "Particle.hpp"
#include "SoftBody1.hpp"
#include "SoftBody2.hpp"
#include "SoftBody3.hpp"
#include "Spring.hpp"
#include "SpringPendulum.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui-SFML.h>
#include <imgui.h>

#include <implot.h>

Application::Application() {
    mSoftBodies.emplace_back(DoubleSpringPendulum(glm::vec2(200.0f, 0.0f), 50.0f, 2.0f, 4.0f));
    mSoftBodies.emplace_back(SoftBody1(glm::vec2(100.0f, 100.0f), 50.0f, 2.0f, 4.0f));
    mSoftBodies.emplace_back(SoftBody2(glm::vec2(300.0f, 200.0f), 50.0f, 2.0f, 4.0f));
    mSoftBodies.emplace_back(SoftBody3(glm::vec2(500.0f, 300.0f), 50.0f, 2.0f, 4.0f, 8));
    mSoftBodies.emplace_back(SpringPendulum(glm::vec2(400.0f, 0.0f), 100.0f, 2.0f, 4.0f));
}

void Application::FixedUpdate(const sf::Time &fixedDeltaTime) {
    const float dt = fixedDeltaTime.asSeconds();
    for (SoftBody &softBody: mSoftBodies) {
        for (Spring &spring: softBody.springs) {
            const glm::vec2 dPosition = spring.mParticle2.position - spring.mParticle1.position;
            const glm::vec2 dVelocity = spring.mParticle2.velocity - spring.mParticle1.velocity;
            if (glm::length(dPosition) != 0) {
                const glm::vec2 force = spring.mSpringConstant * (glm::length(dPosition) - spring.mRestLength) * glm::normalize(dPosition) + spring.mDampingConstant * dVelocity;
                spring.mParticle1.force += force;
                spring.mParticle2.force -= force;
            }
        }
        for (Particle &particle: softBody.particles) {
            const glm::vec2 gravitationalForce = particle.mass * mGravitationalAcceleration;
            particle.force += gravitationalForce;
            if (!particle.pinned) {
                particle.HandleBoundaryCollisions();
                const glm::vec2 acceleration = particle.force / particle.mass;
                particle.velocity += acceleration * dt;
                particle.position += particle.velocity * dt;
            }
            particle.force = glm::vec2(0.0f, 0.0f);
        }
    }
}

void Application::Run() {
    sf::RenderWindow window(mMode, mTitle, mStyle, mSettings);
    window.setFramerateLimit(120u);

    sf::View view = window.getDefaultView();

    (void) ImGui::SFML::Init(window);

    ImPlot::CreateContext();

    const sf::Time fixedDeltaTime = sf::seconds(1.0f / 128.0f);
    const float timeScale = 4.0f;
    sf::Time accumulator = sf::Time::Zero;
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    view.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                    window.setView(view);
                    break;
                default:
                    break;
            }
        }

        const sf::Time deltaTime = deltaClock.restart();
        const sf::Time scaledDeltaTime = timeScale * deltaTime;
        accumulator += scaledDeltaTime;
        while (accumulator > fixedDeltaTime) {
            FixedUpdate(fixedDeltaTime);
            accumulator -= fixedDeltaTime;
        }

        ImGui::SFML::Update(window, deltaTime);

        window.clear(sf::Color(25, 25, 25));

        for (const SoftBody &softBody: mSoftBodies) {
            for (const Spring &spring: softBody.springs) {
                sf::VertexArray line(sf::Lines, 2);
                line[0].position.x = spring.mParticle1.position.x;
                line[0].position.y = spring.mParticle1.position.y;
                line[1].position.x = spring.mParticle2.position.x;
                line[1].position.y = spring.mParticle2.position.y;
                line[0].color = sf::Color(206, 208, 206);
                line[1].color = sf::Color(206, 208, 206);
                window.draw(line);
            }
            for (const Particle &particle: softBody.particles) {
                sf::CircleShape shape;
                shape.setRadius(particle.radius);
                shape.setOrigin(particle.radius, particle.radius);
                shape.setPosition(particle.position.x, particle.position.y);
                shape.setFillColor(sf::Color(230, 232, 230));
                window.draw(shape);
            }
        }

        ImGui::Begin("Statistics");
        ImGui::Text("timeScale       : %.5f", timeScale);
        ImGui::Text("deltaTime       : %.5f", deltaTime.asSeconds());
        ImGui::Text("scaledDeltaTime : %.5f", scaledDeltaTime.asSeconds());
        ImGui::Text("fixedDeltaTime  : %.5f", fixedDeltaTime.asSeconds());
        ImGui::End();

        ImGui::SFML::Render(window);

        window.display();
    }

    ImPlot::DestroyContext();

    ImGui::SFML::Shutdown();
}
