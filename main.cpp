#include "pch.h"
#include "Core/CLIArguments.h"
#include "Engine.h"
#include "Scene/Components/All.h"

using glm::lookAt;
using glm::mat4;
using glm::translate;
using glm::vec3;
using std::make_shared;

auto buildSmallDemoScene(const Engine& engine) {
    auto scene = make_shared<Scene>(engine.getMainWindow().to_any());

    auto triangle = make_shared<Object>();
    {
        auto graphics = make_shared<GraphicsComponent>(triangle.get());
        graphics->vertices = {
            0.0f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
        };

        auto transform = make_shared<TransformComponent>(triangle.get());
        transform->matrix = translate(mat4(1.0f), vec3(-0.7f, 0.7f, 0.0f));

        auto collision = make_shared<CollisionComponent>(triangle.get());
        collision->shpereRadius = 1.0f;

        triangle->addComponent(transform);
        triangle->addComponent(graphics);
        triangle->addComponent(collision);
    }
    scene->addObject(triangle);

    auto square = make_shared<Object>();
    {
        auto graphics = make_shared<GraphicsComponent>(square.get());
        graphics->vertices = {
            -0.5f,  0.5f, 0.0f,
            0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
        };

        auto transform = make_shared<TransformComponent>(square.get());
        transform->matrix = translate(mat4(1.0f), vec3(0.7f, -0.7f, 0.0f));

        auto collision = make_shared<CollisionComponent>(square.get());
        collision->shpereRadius = 1.0f;

        square->addComponent(transform);
        square->addComponent(graphics);
        square->addComponent(collision);
    }
    scene->addObject(square);

    mat4 cameraWordMatrix  = lookAt(
        vec3(0.0f, 0.0f, 3.0f), // позиция камеры
        vec3(0.0f, 0.0f, 0.0f), // цель
        vec3(0.0f, 1.0f, 0.0f)  // вверх
    );
    Frustum frustum(60.f, engine.getMainWindow().getAspectRatio(), 0.1f, 100.f);
    scene->setCamera(make_shared<Camera>(cameraWordMatrix, frustum));

    return scene;
}

int main(int argc, char** argv) {
    CLIArguments args(argc, argv);
    Engine instance(args);
    instance.setScene(buildSmallDemoScene(instance));
    instance.start();
}
