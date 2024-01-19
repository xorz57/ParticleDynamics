#include "Sandbox.hpp"
#include "SandboxLayer.hpp"

Sandbox::Sandbox(const ApplicationSettings &applicationSettings) : Application(applicationSettings) {
    PushLayer(std::make_unique<SandboxLayer>("SandboxLayer"));
}

std::unique_ptr<Application> CreateApplication() {
    ApplicationSettings applicationSettings;
    applicationSettings.width = 600U;
    applicationSettings.height = 600U;
    applicationSettings.title = "Sandbox";
    applicationSettings.fixedDeltaTime = 1.0f / 64.0f;
    applicationSettings.timeScale = 4.0f;
    return std::make_unique<Sandbox>(applicationSettings);
}
