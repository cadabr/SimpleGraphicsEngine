#include "pch.h"
#include "Scene/Subsystems/EventProcessingSubsystem.h"

using std::move;
using std::shared_ptr;

void EventProcessingSubsystem::tick() {
    auto processedEvents = move(events);
    for (const auto& event : processedEvents)
        for (auto listener : listeners)
            listener->onEvent(event);
}

void EventProcessingSubsystem::subscribe(EventListener* listener) {
    listeners.push_back(listener);
}

void EventProcessingSubsystem::pushEvent(shared_ptr<Event> event) {
    events.push_back(event);
}
