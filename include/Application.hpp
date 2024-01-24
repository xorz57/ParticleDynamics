#pragma once

#include "ApplicationSettings.hpp"
#include "SoftBody.hpp"

class Application {
public:
    explicit Application(ApplicationSettings applicationSettings);
    void Run();

private:
    ApplicationSettings mApplicationSettings;
    glm::vec2 mGravitationalAcceleration{0.0f, 10.0f};
    std::vector<SoftBody> mSoftBodies;
};
