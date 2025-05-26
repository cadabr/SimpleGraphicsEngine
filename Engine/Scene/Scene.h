#pragma once
#include "Scene/Camera.h"
#include "Scene/Components/All.h"
#include "Scene/MultiIndex.h"
#include "Scene/Object.h"
#include "Scene/Subsystems/All.h"
#include "Windows/Mouse.h"

class Scene {
public:
    explicit Scene(std::any mainWindowAbstractWrapper);
    Scene(Scene&& other) noexcept;
    Scene& operator=(Scene&& other) noexcept;
    Scene(const Scene&) = delete;
    Scene() = delete;
    Scene& operator=(const Scene&) = delete;

    template <ComponentType Type>
    auto rangeForComponent() const {
        return objects.get<typename tag_for_type<Type>::type>().equal_range(true);
    }

    template<typename SubsystemType>
    SubsystemType* getSubsystem() {
        for(auto& subsystem: subsystems) {
            SubsystemType* s = dynamic_cast<SubsystemType*>(subsystem.get());
            if(s) return s;
        }
        return nullptr;
    }

    void addObject(std::shared_ptr<Object> obj);

    void prepareSubsystems();
    void tick();

    std::shared_ptr<Camera> getCamera() const { return camera; }
    void setCamera(std::shared_ptr<Camera> newCamera) { camera = newCamera; }
    void setMouse(const Mouse& m) { mouse = m; }
    const Mouse& getMouse() const { return mouse; }
    std::any getMainWindowAbstractWrapper() const { return mainWindowAbstractWrapper; }

private:
    std::vector<std::shared_ptr<Subsystem>> subsystems;
    MultiIndex<std::shared_ptr<Object>> objects;
    std::shared_ptr<Camera> camera;
    Mouse mouse;
    std::any mainWindowAbstractWrapper;
};
