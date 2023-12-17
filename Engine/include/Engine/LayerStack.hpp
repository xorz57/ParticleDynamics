#pragma once

#include "Engine/Layer.hpp"

#include <memory>
#include <vector>

namespace Engine {
    class LayerStack {
    public:
        LayerStack() = default;
        void Push(std::unique_ptr<Layer> layer);
        void Pop();
        void Clear();
        void FixedUpdate(float dt) const;
        void Update(float dt) const;
        void LateUpdate(float dt) const;
        void Render(sf::RenderWindow &window) const;
        [[nodiscard]] std::size_t Size() const;

    private:
        std::vector<std::unique_ptr<Layer>> mLayers;
    };
}// namespace Engine
