#pragma once

struct Event {
    virtual ~Event() = default;
};

struct EventListener {
    virtual ~EventListener() = default;
    virtual void onEvent(std::shared_ptr<Event> event) {}
};
