#pragma once
#include "Subsystem.h"

class GraphicsSubsystemImpl;

class GraphicsSubsystem : public Subsystem {
public:
    GraphicsSubsystem();
    ~GraphicsSubsystem();
    void tick(Scene* scene) override;
private:
    std::unique_ptr<GraphicsSubsystemImpl> impl;
};
