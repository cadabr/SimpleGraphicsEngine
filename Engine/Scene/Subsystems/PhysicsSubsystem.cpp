#include "pch.h"
#include "PhysicsSubsystem.h"
#include "Scene/Scene.h"

using std::make_unique;

class PhysicsSubsystemImpl {
public:
    PhysicsSubsystemImpl();
    ~PhysicsSubsystemImpl();
    void tick(Scene* scene);
private:
    std::unique_ptr<btBroadphaseInterface> broadphase;
    std::unique_ptr<btDefaultCollisionConfiguration> collisionConfig;
    std::unique_ptr<btCollisionDispatcher> dispatcher;
    std::unique_ptr<btCollisionWorld> collisionWorld;
};

PhysicsSubsystemImpl::PhysicsSubsystemImpl()
: broadphase(make_unique<btDbvtBroadphase>())
, collisionConfig(make_unique<btDefaultCollisionConfiguration>())
, dispatcher(make_unique<btCollisionDispatcher>(collisionConfig.get()))
, collisionWorld(make_unique<btCollisionWorld>(dispatcher.get(), broadphase.get(), collisionConfig.get())) {
}

PhysicsSubsystemImpl::~PhysicsSubsystemImpl() {
}

void PhysicsSubsystemImpl::tick(Scene* scene) {
}

PhysicsSubsystem::PhysicsSubsystem()
: impl(make_unique<PhysicsSubsystemImpl>()) {
}

PhysicsSubsystem::~PhysicsSubsystem() = default;

void PhysicsSubsystem::tick(Scene* scene) {
    impl->tick(scene);
}
