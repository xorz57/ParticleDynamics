#include "Sandbox.hpp"
#include "SandboxLayer.hpp"

Sandbox::Sandbox(const ApplicationSettings &applicationSettings) : Application(applicationSettings) {
    PushLayer(std::make_unique<SandboxLayer>("SandboxLayer"));
}
