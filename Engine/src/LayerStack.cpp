#include "Engine/LayerStack.hpp"

using namespace Engine;

void LayerStack::Push(std::unique_ptr<Layer> layer) {
    mLayers.push_back(std::move(layer));
    mLayers.back()->OnAttach();
}

void LayerStack::Pop() {
    if (!mLayers.empty()) {
        mLayers.back()->OnDetach();
        mLayers.pop_back();
    }
}

void LayerStack::Clear() {
    for (const std::unique_ptr<Layer> &layer: mLayers) {
        layer->OnDetach();
    }
    mLayers.clear();
}

void LayerStack::FixedUpdate(float dt) const {
    for (const std::unique_ptr<Layer> &layer: mLayers) {
        layer->OnFixedUpdate(dt);
    }
}

void LayerStack::Update(float dt) const {
    for (const std::unique_ptr<Layer> &layer: mLayers) {
        layer->OnUpdate(dt);
    }
}

void LayerStack::LateUpdate(float dt) const {
    for (const std::unique_ptr<Layer> &layer: mLayers) {
        layer->OnLateUpdate(dt);
    }
}

void LayerStack::Render(sf::RenderWindow &window) const {
    for (const std::unique_ptr<Layer> &layer: mLayers) {
        layer->OnRender(window);
    }
}

std::size_t LayerStack::Size() const {
    return mLayers.size();
}
