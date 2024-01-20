#include "Application.hpp"
#include "Logging.hpp"
#include "Sandbox.hpp"

#include <cstdlib>
#include <memory>

std::unique_ptr<Application> CreateApplication() {
    ApplicationSettings applicationSettings;
    applicationSettings.width = 600U;
    applicationSettings.height = 600U;
    applicationSettings.title = "Sandbox";
    applicationSettings.fixedDeltaTime = 1.0f / 64.0f;
    applicationSettings.timeScale = 4.0f;
    return std::make_unique<Sandbox>(applicationSettings);
}

int main() {
    Logging::Init();
    std::unique_ptr<Application> application = CreateApplication();
    application->Run();
    return EXIT_SUCCESS;
}
