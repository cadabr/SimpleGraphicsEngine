#include "pch.h"
#include "Scene/Scene.h"
#include "Scene/Subsystems/PhysicsSubsystem.h"

using std::make_unique;
using std::unique_ptr;

class PhysicsSubsystemImpl {
public:
    PhysicsSubsystemImpl(PhysicsSubsystem& interface);
    ~PhysicsSubsystemImpl();
    void tick();
private:
    PhysicsSubsystem& interface;
    unique_ptr<btBroadphaseInterface> broadphase;
    unique_ptr<btDefaultCollisionConfiguration> collisionConfig;
    unique_ptr<btCollisionDispatcher> dispatcher;
    unique_ptr<btCollisionWorld> collisionWorld;
};

PhysicsSubsystemImpl::PhysicsSubsystemImpl(PhysicsSubsystem& interface)
: interface(interface)
, broadphase(make_unique<btDbvtBroadphase>())
, collisionConfig(make_unique<btDefaultCollisionConfiguration>())
, dispatcher(make_unique<btCollisionDispatcher>(collisionConfig.get()))
, collisionWorld(make_unique<btCollisionWorld>(dispatcher.get(), broadphase.get(), collisionConfig.get())) {
}

PhysicsSubsystemImpl::~PhysicsSubsystemImpl() {
}

void PhysicsSubsystemImpl::tick() {
}

PhysicsSubsystem::PhysicsSubsystem(Scene& scene)
: Subsystem(scene)
, impl(make_unique<PhysicsSubsystemImpl>(*this)) {
}

PhysicsSubsystem::~PhysicsSubsystem() = default;

void PhysicsSubsystem::tick() {
    impl->tick();
}
