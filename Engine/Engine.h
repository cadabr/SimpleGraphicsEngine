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
    //std::shared_ptr<Scene> getScene() const { return scene; }
    const MainWindow& getMainWindow() const { return mainWindow; }
private:
    void mainLoop();
private:
    CLIArguments cliArguments;
    MainWindow mainWindow;
    std::shared_ptr<Scene> scene;
};
