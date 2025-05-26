#include "Engine.h"
#include "Scene/Subsystems/All.h"

using std::move;
using std::shared_ptr;

template<> Engine* ExplicitSingleton<Engine>::s_instance = nullptr;

Engine::Engine(const CLIArguments& args)
: cliArguments(args)
, mainWindow("SimpleGraphicsEngine", 1024u, 768u) {
}

void Engine::start() {
    scene->prepareSubsystems();
    mainLoop();
}

void Engine::mainLoop() {
    while(mainWindow.pollEvents() != MainWindowState::DestroyPending) {
        scene->setMouse(mainWindow.getMouse());
        scene->tick();
    }
}

shared_ptr<Scene> Engine::setScene(shared_ptr<Scene> newScene) {
    auto oldScene = move(scene);
    scene = move(newScene);
    return oldScene;
}
