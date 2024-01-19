#pragma once

#include "ApplicationSettings.hpp"
#include "LayerStack.hpp"

class Application {
public:
    explicit Application(ApplicationSettings applicationSettings);
    virtual ~Application() = default;
    void PushLayer(std::unique_ptr<Layer> layer);
    void PopLayer();
    void Run();

private:
    ApplicationSettings mApplicationSettings;
    LayerStack mLayerStack;
};
