#pragma once
#include "Scene/Subsystems/Subsystem.h"

class GraphicsSubsystemImpl;

class GraphicsSubsystem : public Subsystem {
public:
    GraphicsSubsystem(std::any mainWindow);
    ~GraphicsSubsystem();
    void tick(Scene* scene) override;
private:
    std::unique_ptr<GraphicsSubsystemImpl> impl;
};
