#pragma once
#include "Scene/Components/Component.h"

class KinematicsComponent : public Component {
public:
    DEFINE_COMPONENT(KinematicsComponent, ComponentType::Kinematics);
};
