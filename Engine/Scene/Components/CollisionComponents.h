#pragma once
#include "Scene/Components/Component.h"

class CollisionComponent : public Component {
public:
    DEFINE_COMPONENT(CollisionComponent, ComponentType::Collision);
    float shpereRadius = 1.0f;
};
