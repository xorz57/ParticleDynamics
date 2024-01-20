#include "Application.hpp"
#include "Logging.hpp"

#include <cstdlib>
#include <memory>

int main() {
    Logging::Init();

    ApplicationSettings applicationSettings;
    applicationSettings.width = 600U;
    applicationSettings.height = 600U;
    applicationSettings.title = "ParticlePhysics";
    applicationSettings.fixedDeltaTime = 1.0f / 64.0f;
    applicationSettings.timeScale = 4.0f;

    std::unique_ptr<Application> application = std::make_unique<Application>(applicationSettings);

    application->Run();

    return EXIT_SUCCESS;
}
