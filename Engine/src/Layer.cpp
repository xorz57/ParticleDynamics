#include "Engine/Layer.hpp"

using namespace Engine;

Layer::Layer(std::string name) : mName(std::move(name)) {}

std::string Layer::GetName() const {
    return mName;
}
