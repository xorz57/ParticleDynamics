#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>

class Layer {
public:
    explicit Layer(std::string name);
    virtual ~Layer() = default;
    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;
    virtual void OnFixedUpdate(float dt) = 0;
    virtual void OnUpdate(float dt) = 0;
    virtual void OnLateUpdate(float dt) = 0;
    virtual void OnRender(sf::RenderWindow &window) = 0;
    [[nodiscard]] std::string GetName() const;

private:
    std::string mName;
};
