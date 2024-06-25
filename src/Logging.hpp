#pragma once

#include <spdlog/spdlog.h>

#include <memory>

class Logging {
public:
    static void init();
    inline static std::shared_ptr<spdlog::logger> &getServerLogger() { return sServerLogger; }
    inline static std::shared_ptr<spdlog::logger> &getClientLogger() { return sClientLogger; }

private:
    static std::shared_ptr<spdlog::logger> sServerLogger;
    static std::shared_ptr<spdlog::logger> sClientLogger;
};

#define SERVER_TRACE(...) Logging::getServerLogger()->trace(__VA_ARGS__)
#define SERVER_INFO(...) Logging::getServerLogger()->info(__VA_ARGS__)
#define SERVER_WARN(...) Logging::getServerLogger()->warn(__VA_ARGS__)
#define SERVER_ERROR(...) Logging::getServerLogger()->error(__VA_ARGS__)

#define CLIENT_TRACE(...) Logging::getClientLogger()->trace(__VA_ARGS__)
#define CLIENT_INFO(...) Logging::getClientLogger()->info(__VA_ARGS__)
#define CLIENT_WARN(...) Logging::getClientLogger()->warn(__VA_ARGS__)
#define CLIENT_ERROR(...) Logging::getClientLogger()->error(__VA_ARGS__)
