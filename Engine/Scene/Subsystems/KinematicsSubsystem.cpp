#include "pch.h"
#include "Scene/Events/All.h"
#include "Scene/Subsystems/EventProcessingSubsystem.h"
#include "Scene/Subsystems/KinematicsSubsystem.h"
#include "Scene/Scene.h"

using std::shared_ptr;

KinematicsSubsystem::KinematicsSubsystem(Scene& scene)
: Subsystem(scene) {
    scene.getSubsystem<EventProcessingSubsystem>()->subscribe(this);
}

void KinematicsSubsystem::tick() {
}

void KinematicsSubsystem::onEvent(shared_ptr<Event> event) {
    if(auto rayHitObject = dynamic_cast<RayHitObject*>(event.get()); rayHitObject) {
        // TODO: Fill me
    }
}