#include "pch.h"
#include "Components/All.h"
#include "Core.h"
#include "Engine.h"

using std::make_shared;
using std::shared_ptr;

auto buildSmallDemoScene() {
    shared_ptr<Scene> scene = make_shared<Scene>();
    auto obj1 = make_shared<Object>();
    obj1->addComponent(make_shared<TransformComponent>(obj1.get()));
    obj1->addComponent(make_shared<GraphicsComponent>(obj1.get()));
    scene->addObject(obj1);
    return scene;
}

int main(int argc, char** argv) {
    Parameters params(argc, argv);
    Engine instance(params);
    instance.setScene(buildSmallDemoScene());
    instance.start();
}