#include "Application.hpp"
#include "Logging.hpp"

#include <cstdlib>

int main() {
    Logging::Init();
    Application application;
    application.Run();
    return EXIT_SUCCESS;
}
