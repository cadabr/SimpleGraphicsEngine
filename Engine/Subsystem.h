#pragma once

class Scene;

class Subsystem {
public:
    virtual ~Subsystem() = default;
    virtual void tick() = 0;
};
