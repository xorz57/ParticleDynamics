#pragma once

#include "Engine/Layer.hpp"
#include "Engine/SoftBody.hpp"

#include <memory>
#include <vector>

class SandboxLayer : public Engine::Layer {
public:
    explicit SandboxLayer(std::string name);
    void OnAttach() override;
    void OnDetach() override;
    void OnFixedUpdate(float dt) override;
    void OnUpdate(float dt) override;
    void OnLateUpdate(float dt) override;
    void OnRender(sf::RenderWindow &window) override;

private:
    glm::vec2 mGravitationalAcceleration{0.0f, 10.0f};
    std::vector<std::unique_ptr<Engine::SoftBody>> mSoftBodies;
};
