#pragma once
#include "Scene/Subsystems/Subsystem.h"
#include "Windows/Mouse.h"

class InputProcessingSubsystem : public Subsystem {
public:
    InputProcessingSubsystem(Scene& scene) : Subsystem(scene) {}
    void tick() override;
private:
    Mouse prevMouse;
};
