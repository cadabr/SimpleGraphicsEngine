#include "Engine.h"
#include "Subsystems/All.h"

using std::make_shared;
using std::move;
using std::shared_ptr;
using std::swap;

template<> Engine* ExplicitSingleton<Engine>::s_instance = nullptr;

Engine::Engine(const Parameters& params)
: parameters(params)
, subsystems({
    {make_shared<GraphicsSubsystem>()},
    {make_shared<KinematicsSubsystem>()}
}) {
}

void Engine::start() {
    while(true) {
        for(auto subsystem: subsystems) {
            subsystem->tick(scene.get());
        }
    }
}

shared_ptr<Scene> Engine::setScene(shared_ptr<Scene> newScene)
{
    auto oldScene = move(scene);
    scene = move(newScene);
    return oldScene;
}
