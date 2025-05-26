#include "pch.h"
#include "Scene/Events/All.h"
#include "Scene/Scene.h"
#include "Scene/Subsystems/EventProcessingSubsystem.h"
#include "Scene/Subsystems/InputProcessingSubsystem.h"

using std::make_shared;

void InputProcessingSubsystem::tick() {
    const Mouse& currMouse = scene.getMouse();
    if(currMouse.isPressed(MouseButton::Left) && !prevMouse.isPressed(MouseButton::Left)) {
        auto leftButtonDown = make_shared<MouseButtonPressed>(MouseButton::Left, currMouse.position);
        scene.getSubsystem<EventProcessingSubsystem>()->pushEvent(leftButtonDown);
    }
    if(currMouse.isPressed(MouseButton::Right) && !prevMouse.isPressed(MouseButton::Right)) {
    }
    prevMouse = currMouse;
}
