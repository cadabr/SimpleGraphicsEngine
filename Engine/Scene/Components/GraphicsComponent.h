#pragma once
#include "Scene/Component.h"

class GraphicsComponent : public Component {
public:
    DEFINE_COMPONENT(GraphicsComponent, ComponentType::Graphics);
    std::vector<float> vertices;
};
