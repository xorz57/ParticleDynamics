#pragma once

#include <spdlog/spdlog.h>

#include <memory>

namespace Engine {
    class Logging {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger> &GetServerLogger() { return sServerLogger; }
        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return sClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> sServerLogger;
        static std::shared_ptr<spdlog::logger> sClientLogger;
    };
}// namespace Engine

#define SERVER_TRACE(...) Engine::Logging::GetServerLogger()->trace(__VA_ARGS__)
#define SERVER_INFO(...) Engine::Logging::GetServerLogger()->info(__VA_ARGS__)
#define SERVER_WARN(...) Engine::Logging::GetServerLogger()->warn(__VA_ARGS__)
#define SERVER_ERROR(...) Engine::Logging::GetServerLogger()->error(__VA_ARGS__)

#define CLIENT_TRACE(...) Engine::Logging::GetClientLogger()->trace(__VA_ARGS__)
#define CLIENT_INFO(...) Engine::Logging::GetClientLogger()->info(__VA_ARGS__)
#define CLIENT_WARN(...) Engine::Logging::GetClientLogger()->warn(__VA_ARGS__)
#define CLIENT_ERROR(...) Engine::Logging::GetClientLogger()->error(__VA_ARGS__)
