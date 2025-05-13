#pragma once
#include "Core.h"
#include "Components/All.h"
#include "Object.h"
#include "Scene.h"

class Game {
public:
    Game(const LaunchParameters& params) {
    }

    void start() {
        // Механика инциализации Object требует доработки
        auto obj1 = std::make_shared<Object>();
        obj1->addComponent(std::make_shared<TransformComponent>(obj1.get()));
        obj1->addComponent(std::make_shared<GraphicsComponent>(obj1.get()));

        scene.addObject(obj1);

        auto [beginRenderer, endRenderer] = scene.rangeForComponent<ComponentType::Graphics>();
        for (auto it = beginRenderer; it != endRenderer; ++it) {
            (*it).get();
        }
    }

private:
    Scene scene;
};