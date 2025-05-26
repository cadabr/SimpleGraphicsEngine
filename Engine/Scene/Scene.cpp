#include "pch.h"
#include "Scene/Scene.h"

using std::any;
using std::make_shared;
using std::move;
using std::shared_ptr;
using std::vector;

Scene::Scene(any mainWindowAbstractWrapper)
: mainWindowAbstractWrapper(mainWindowAbstractWrapper) {
}

Scene::Scene(Scene&& other) noexcept
: subsystems(move(other.subsystems))
, objects(std::move(other.objects))
, camera(move(other.camera))
, mouse(move(other.mouse))
, mainWindowAbstractWrapper(move(other.mainWindowAbstractWrapper)) {
}

Scene& Scene::operator=(Scene&& other) noexcept {
    if (this != &other) {
        subsystems = move(other.subsystems);
        objects = std::move(other.objects);
        camera = move(other.camera);
        mouse = move(other.mouse);
        mainWindowAbstractWrapper = move(other.mainWindowAbstractWrapper);
    }
    return *this;
}
void Scene::addObject(shared_ptr<Object> obj) {
    objects.insert(move(obj));
}

void Scene::prepareSubsystems() {
    // EventProcessingSubsystem необходимо инициализировать прежде чем станет возможна подписка на события
    subsystems.push_back({ make_shared<EventProcessingSubsystem >(*this)});
    subsystems.push_back({ make_shared<GraphicsSubsystem        >(*this)});
    subsystems.push_back({ make_shared<InputProcessingSubsystem >(*this)});
    subsystems.push_back({ make_shared<KinematicsSubsystem      >(*this)});
    subsystems.push_back({ make_shared<PhysicsSubsystem         >(*this)});
    subsystems.push_back({ make_shared<RaycastSubsystem         >(*this)});
}

void Scene::tick() {
    for(auto subsystem: subsystems) {
        subsystem->tick();
    }
}
