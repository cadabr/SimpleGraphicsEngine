#pragma once
#include "Engine.h"
#include "Subsystem.h"
#include "Components/GraphicsComponent.h"
#include "Components/TransformComponent.h"

class GraphicsSubsystem : public Subsystem {
public:
    GraphicsSubsystem();

    void tick(Scene* scene) override;
};
