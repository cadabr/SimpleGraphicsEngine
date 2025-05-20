#pragma once

#include "Scene/Camera.h"
#include "Scene/Components/All.h"
#include "Scene/MultiIndex.h"
#include "Scene/Object.h"
#include "Scene/Subsystems/All.h"

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

    const Camera& getCamera() const { return camera; }

private:
    MultiIndex<std::shared_ptr<Object>> objects;
    Camera camera;
};
