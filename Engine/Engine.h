#pragma once
#include "Scene/Scene.h"
#include "Core/CLIArguments.h"
#include "Core/ExplicitSingleton.h"
#include "Windows/MainWindow.h"

class Engine : public ExplicitSingleton<Engine> {
public:
    Engine(const CLIArguments& argc);
    void start();
    const CLIArguments& getCLIArguments() const { return cliArguments; }
    std::shared_ptr<Scene> setScene(std::shared_ptr<Scene> stranger);
    std::shared_ptr<Scene> getScene() const { return scene; }
private:
    void prepareSceneSubsystems();
    void mainLoop();
private:
    CLIArguments cliArguments;
    std::shared_ptr<Scene> scene;
    std::vector<std::shared_ptr<Subsystem>> subsystems;
    MainWindow window;
};
