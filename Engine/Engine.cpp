#include "Engine.h"
#include "Subsystems/All.h"

using std::make_shared;
using std::move;

template<> Engine* ExplicitSingleton<Engine>::s_instance = nullptr;

Engine::Engine(const Parameters& params)
: parameters(params)
, subsystems({
    {make_shared<GraphicsSubsystem>()},
    {make_shared<KinematicsSubsystem>()}
}) {
}

void Engine::start() {
    for(auto subsystem: subsystems) {
        subsystem->tick(scene.get());
    }
}

std::shared_ptr<Scene> Engine::setScene(std::shared_ptr<Scene> newScene)
{
    auto prevScene = move(scene);
    scene = move(newScene);
    return scene;
}
