#pragma once
#include "Scene/Subsystems/Subsystem.h"

class GraphicsSubsystemImpl;

class GraphicsSubsystem : public Subsystem {
public:
    GraphicsSubsystem(Scene& scene);
    ~GraphicsSubsystem();
    void tick() override;
private:
    friend class GraphicsSubsystemImpl;
    std::unique_ptr<GraphicsSubsystemImpl> impl;
};
