#pragma once
#include "Scene/Events/Event.h"

class Scene;

class Subsystem : public EventListener {
public:
    Subsystem() = delete;
    Subsystem(Scene& scene) : scene(scene) {}
    virtual ~Subsystem() = default;
    virtual void tick() = 0;
protected:
    Scene& scene;
};
