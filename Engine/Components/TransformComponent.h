#pragma once
#include "Component.h"

class TransformComponent : public Component {
public:
    DEFINE_COMPONENT(TransformComponent, ComponentType::Transform);

    std::array<GLfloat, 16> matrix;
};
