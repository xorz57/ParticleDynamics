#include "Application.hpp"
#include "Logging.hpp"

#include <cstdlib>

int main() {
    Logging::Init();

    ApplicationSettings applicationSettings;
    applicationSettings.width = 600u;
    applicationSettings.height = 600u;
    applicationSettings.title = "ParticlePhysics";
    applicationSettings.fixedDeltaTime = 1.0f / 128.0f;
    applicationSettings.timeScale = 4.0f;

    Application application(applicationSettings);
    application.Run();

    return EXIT_SUCCESS;
}
