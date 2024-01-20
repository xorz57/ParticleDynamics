#include "Application.hpp"
#include "World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/WindowStyle.hpp>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui-SFML.h>

#include <implot.h>

Application::Application(ApplicationSettings applicationSettings) : mApplicationSettings(std::move(applicationSettings)) {
    PushLayer(std::make_unique<World>("World"));
}

void Application::PushLayer(std::unique_ptr<Layer> layer) {
    mLayerStack.Push(std::move(layer));
}

void Application::PopLayer() {
    mLayerStack.Pop();
}

void Application::Run() {
    sf::ContextSettings settings;
    settings.depthBits = 24U;
    settings.stencilBits = 8U;
    settings.antialiasingLevel = 8U;
    settings.majorVersion = 3U;
    settings.minorVersion = 0U;

    sf::RenderWindow window({mApplicationSettings.width, mApplicationSettings.height}, mApplicationSettings.title, sf::Style::Default, settings);
    window.setFramerateLimit(120U);

    sf::View view = window.getDefaultView();

    (void) ImGui::SFML::Init(window);

    ImPlot::CreateContext();

    const sf::Time fixedDeltaTime = sf::seconds(mApplicationSettings.fixedDeltaTime);
    const float timeScale = mApplicationSettings.timeScale;
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
        accumulator += timeScale * deltaTime;
        while (accumulator > fixedDeltaTime) {
            mLayerStack.FixedUpdate(fixedDeltaTime.asSeconds());
            accumulator -= fixedDeltaTime;
        }

        ImGui::SFML::Update(window, deltaTime);

        mLayerStack.Update(deltaTime.asSeconds());
        mLayerStack.LateUpdate(deltaTime.asSeconds());
        window.clear(sf::Color(25, 25, 25));
        mLayerStack.Render(window);

        ImGui::Begin("Settings");
        ImGui::Text("deltaTime      : %.5lf", deltaTime.asSeconds());
        ImGui::Text("fixedDeltaTime : %.5lf", fixedDeltaTime.asSeconds());
        ImGui::End();

        ImGui::SFML::Render(window);

        window.display();
    }
    mLayerStack.Clear();

    ImPlot::DestroyContext();

    ImGui::SFML::Shutdown();
}
