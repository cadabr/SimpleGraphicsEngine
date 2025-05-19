#pragma once
#include "Components/Component.h"

class Object {
public:
    void addComponent(std::shared_ptr<Component> c) {
        components[c->getType()] = std::move(c);
    }

    Component* getComponentByType(ComponentType type) const {
        auto it = components.find(type);
        return it != components.end() ? it->second.get() : nullptr;
    }

    template<typename T>
    T* getComponent() const {
        return static_cast<T*>(getComponentByType(T::TypeID));
    }

    bool hasComponent(ComponentType type) const {
        return getComponentByType(type);
    }

private:
    std::unordered_map<ComponentType, std::shared_ptr<Component>> components;
};
