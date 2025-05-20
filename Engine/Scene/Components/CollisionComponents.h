#pragma once
#include "Scene/Components/Component.h"

class CollisionsComponent : public Component {
public:
    DEFINE_COMPONENT(CollisionsComponent, ComponentType::Collision);
    float shpereRadius = 1.0f;
};
