#pragma once

#include "Engine/ApplicationSettings.hpp"
#include "Engine/LayerStack.hpp"

namespace Engine {
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
}// namespace Engine
