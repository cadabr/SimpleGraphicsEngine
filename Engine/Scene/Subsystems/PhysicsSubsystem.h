#pragma once
#include "Scene/Subsystems/Subsystem.h"

class PhysicsSubsystemImpl;

class PhysicsSubsystem : public Subsystem {
public:
    PhysicsSubsystem();
    ~PhysicsSubsystem();
    void tick(Scene* scene) override;
private:
    std::unique_ptr<PhysicsSubsystemImpl> impl;
};
