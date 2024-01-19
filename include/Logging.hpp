#pragma once

#include <spdlog/spdlog.h>

#include <memory>

class Logging {
public:
    static void Init();
    inline static std::shared_ptr<spdlog::logger> &GetServerLogger() { return sServerLogger; }
    inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return sClientLogger; }

private:
    static std::shared_ptr<spdlog::logger> sServerLogger;
    static std::shared_ptr<spdlog::logger> sClientLogger;
};

#define SERVER_TRACE(...) Logging::GetServerLogger()->trace(__VA_ARGS__)
#define SERVER_INFO(...) Logging::GetServerLogger()->info(__VA_ARGS__)
#define SERVER_WARN(...) Logging::GetServerLogger()->warn(__VA_ARGS__)
#define SERVER_ERROR(...) Logging::GetServerLogger()->error(__VA_ARGS__)

#define CLIENT_TRACE(...) Logging::GetClientLogger()->trace(__VA_ARGS__)
#define CLIENT_INFO(...) Logging::GetClientLogger()->info(__VA_ARGS__)
#define CLIENT_WARN(...) Logging::GetClientLogger()->warn(__VA_ARGS__)
#define CLIENT_ERROR(...) Logging::GetClientLogger()->error(__VA_ARGS__)
