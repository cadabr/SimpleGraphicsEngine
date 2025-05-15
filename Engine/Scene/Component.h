#pragma once

enum class ComponentType {
    Graphics,
    Kinematics,
    Transform,
    ENUM_SIZE
};

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
