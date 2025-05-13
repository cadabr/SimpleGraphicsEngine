#pragma once
#include "Component.h"

class GraphicsComponent : public Component {
public:
    DEFINE_COMPONENT(GraphicsComponent, ComponentType::Graphics);
};
