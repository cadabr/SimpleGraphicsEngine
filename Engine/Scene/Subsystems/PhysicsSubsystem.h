#pragma once
#include "Scene/Subsystems/Subsystem.h"

class PhysicsSubsystemImpl;

class PhysicsSubsystem : public Subsystem {
public:
    PhysicsSubsystem(Scene& scene);
    ~PhysicsSubsystem();
    void tick() override;
private:
    friend class PhysicsSubsystemImpl;
    std::unique_ptr<PhysicsSubsystemImpl> impl;
};
