#pragma once
#include "Scene/Events/Event.h"
#include "Windows/Mouse.h"

class Object;

struct MouseButtonPressed : Event {
    MouseButtonPressed() = delete;
    MouseButtonPressed(MouseButton btn, MousePosition position) : button(button), position(position) {}
    MouseButton button;
    MousePosition position;
};

struct RayHitObject : Event {
    RayHitObject() = delete;
    RayHitObject(std::shared_ptr<Object> object) : object(object) {}
    std::shared_ptr<Object> object;
};
