#include "Logging.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Logging::sServerLogger;
std::shared_ptr<spdlog::logger> Logging::sClientLogger;

void Logging::Init() {
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    sServerLogger = spdlog::stdout_color_mt("Engine");
    sClientLogger = spdlog::stdout_color_mt("Client");
    sServerLogger->set_level(spdlog::level::trace);
    sClientLogger->set_level(spdlog::level::trace);
}
