#pragma once
#include "Scene/Component.h"

class TransformComponent : public Component {
public:
    DEFINE_COMPONENT(TransformComponent, ComponentType::Transform);
    glm::mat4 matrix;
};
