#pragma once

#include "Layer.hpp"
#include "SoftBody.hpp"

#include <memory>
#include <vector>

class World : public Layer {
public:
    explicit World(std::string name);
    void OnAttach() override;
    void OnDetach() override;
    void OnFixedUpdate(float dt) override;
    void OnUpdate(float dt) override;
    void OnLateUpdate(float dt) override;
    void OnRender(sf::RenderWindow &window) override;

private:
    glm::vec2 mGravitationalAcceleration{0.0f, 10.0f};
    std::vector<std::unique_ptr<SoftBody>> mSoftBodies;
};
