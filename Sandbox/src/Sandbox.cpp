#include "Sandbox/Sandbox.hpp"
#include "Sandbox/SandboxLayer.hpp"

Sandbox::Sandbox(const Engine::ApplicationSettings &applicationSettings) : Engine::Application(applicationSettings) {
    PushLayer(std::make_unique<SandboxLayer>("SandboxLayer"));
}

std::unique_ptr<Engine::Application> Engine::CreateApplication() {
    Engine::ApplicationSettings applicationSettings;
    applicationSettings.width = 600U;
    applicationSettings.height = 600U;
    applicationSettings.title = "Sandbox";
    applicationSettings.fixedDeltaTime = 1.0f / 600.0f;
    applicationSettings.timeScale = 4.0f;
    return std::make_unique<Sandbox>(applicationSettings);
}
