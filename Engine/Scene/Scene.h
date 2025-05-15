#pragma once
#include "Object.h"
#include "MultiIndex.h"

class Scene {
public:
    Scene() = default;

    Scene(Scene&& other) noexcept {
        objects = std::move(other.objects);
    }

    Scene& operator=(Scene&& other) noexcept {
        if (this != &other) {
            objects = std::move(other.objects);
        }
        return *this;
    }

    void addObject(std::shared_ptr<Object> obj) {
        objects.insert(std::move(obj));
    }

    template <ComponentType Type>
    auto rangeForComponent() const {
        return objects.get<typename tag_for_type<Type>::type>().equal_range(true);
    }

private:
    MultiIndex<std::shared_ptr<Object>> objects;
};
