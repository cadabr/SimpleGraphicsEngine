#pragma once
#include "Scene/Subsystems/Subsystem.h"

class KinematicsSubsystem : public Subsystem {
public:
    KinematicsSubsystem(Scene& scene);
    void tick() override;
    void onEvent(std::shared_ptr<Event> event) override;
};
