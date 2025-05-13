#pragma once

#include "ComponentTypeReg.h"

class Object;

class Component {
public:
    Component(Object* owner) : owner(owner) {}
    virtual ~Component() = default;
    virtual ComponentType getType() const = 0;
protected:
    Object* owner;
};

#define DEFINE_COMPONENT(ComponentName, ComponentId)            \
    ComponentName(Object* owner) : Component(owner) {}          \
    static constexpr ComponentType TypeID = ComponentId;        \
    ComponentType getType() const override { return TypeID; }
