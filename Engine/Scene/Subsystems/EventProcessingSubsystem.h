#pragma once
#include "Scene/Events/Event.h"
#include "Scene/Subsystems/Subsystem.h"

class EventProcessingSubsystem : public Subsystem {
public:
    EventProcessingSubsystem(Scene& scene) : Subsystem(scene) {}
    void tick() override;
    void subscribe(EventListener* listener);
    void pushEvent(std::shared_ptr<Event> event);
private:
    std::vector<EventListener*> listeners;
    std::vector<std::shared_ptr<Event>> events;
};
