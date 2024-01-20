#include "Application.hpp"
#include "Logging.hpp"

#include <cstdlib>
#include <memory>

std::unique_ptr<Application> CreateApplication();

int main() {
    Logging::Init();
    std::unique_ptr<Application> application = CreateApplication();
    application->Run();
    return EXIT_SUCCESS;
}
