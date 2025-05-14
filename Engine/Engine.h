#pragma once
#include "Core.h"
#include "ExplicitSingleton.h"
#include "Scene.h"
#include "Subsystem.h"

class Engine : public ExplicitSingleton<Engine> {
public:
    Engine(const Parameters& params);

    void start();

    const Parameters& getParameters() const { return parameters; }

    std::shared_ptr<Scene> setScene(std::shared_ptr<Scene> newScene);

    std::shared_ptr<Scene> getScene() { return scene; }

private:
    Parameters parameters;
    std::shared_ptr<Scene> scene;
    std::vector<std::shared_ptr<Subsystem>> subsystems;
};
