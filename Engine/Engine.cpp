#include "Engine.h"
#include "Scene/Subsystems/All.h"

using std::make_shared;
using std::move;
using std::shared_ptr;
using std::swap;
using std::vector;

template<> Engine* ExplicitSingleton<Engine>::s_instance = nullptr;

Engine::Engine(const CLIArguments& args)
: cliArguments(args)
, subsystems({}) {
}

void Engine::start() {
    prepareSceneSubsystems();
    mainLoop();
}

void Engine::mainLoop() {
    while(true) {
        for(auto subsystem: subsystems) {
            subsystem->tick(scene.get());
        }
        if(window.pollEvents() == MainWindowState::DestroyPending) {
            break;
        }
    }
}

shared_ptr<Scene> Engine::setScene(shared_ptr<Scene> newScene) {
    auto oldScene = move(scene);
    scene = move(newScene);
    return oldScene;
}

void Engine::prepareSceneSubsystems() {
    subsystems = move(vector<shared_ptr<Subsystem>> {
        {make_shared<GraphicsSubsystem>(window.to_any())},
        {make_shared<KinematicsSubsystem>()}
    });
}
