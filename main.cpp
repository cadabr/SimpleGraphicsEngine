#include "pch.h"
#include "Object.h"
#include "Components/GraphicsComponent.h"
#include "Components/TransformComponent.h"

int main(int argc, char** argv) {
    // LaunchParameters params(argc, argv);
    // Game game(params);
    // game.startMainLoop();

    Object obj;

    obj.addComponent(std::make_shared<GraphicsComponent>(&obj));
    obj.addComponent(std::make_shared<TransformComponent>(&obj));

    auto* transform = obj.getComponent<TransformComponent>();
    auto* graphics = obj.getComponent<GraphicsComponent>();

    assert(transform != nullptr);
    assert(graphics != nullptr);

    return 0;
}