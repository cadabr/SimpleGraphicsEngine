#pragma once
#include "Scene/Components/Component.h"

class TransformComponent : public Component {
public:
    DEFINE_COMPONENT(TransformComponent, ComponentType::Transform);
    glm::mat4 matrix;
};
