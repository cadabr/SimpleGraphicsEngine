#pragma once
#include "Scene/Component.h"

class KinematicsComponent : public Component {
public:
    DEFINE_COMPONENT(KinematicsComponent, ComponentType::Kinematics);
};
