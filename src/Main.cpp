#include "Application.hpp"
#include "Logging.hpp"

#include <cstdlib>

int main() {
    Logging::init();
    Application application;
    application.run();
    return EXIT_SUCCESS;
}
