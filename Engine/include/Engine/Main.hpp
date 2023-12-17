#pragma once

#include "Engine/Application.hpp"
#include "Engine/Logging.hpp"

#include <cstdlib>
#include <memory>

namespace Engine {
    std::unique_ptr<Application> CreateApplication();
}// namespace Engine

int main() {
    using namespace Engine;
    Logging::Init();
    std::unique_ptr<Application> application = CreateApplication();
    application->Run();
    return EXIT_SUCCESS;
}
