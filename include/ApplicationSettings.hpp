#pragma once

#include <string>

struct ApplicationSettings {
    unsigned int width{0U};
    unsigned int height{0U};
    std::string title;
    float fixedDeltaTime{1.0f / 64.0f};
    float timeScale{1.0f};
};
