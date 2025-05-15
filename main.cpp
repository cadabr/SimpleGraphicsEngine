#include "pch.h"
#include "Components/All.h"
#include "Core.h"
#include "Engine.h"

using std::copy;
using std::make_shared;
using std::shared_ptr;

auto buildSmallDemoScene() {
    auto scene = make_shared<Scene>();

    auto triangle = make_shared<Object>();
    {
        auto graphics = make_shared<GraphicsComponent>(triangle.get());
        triangle->addComponent(graphics);
        graphics->vertices = {
            0.0f,  0.5f, 0.0f,
           -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
        };

        auto transform = make_shared<TransformComponent>(triangle.get());
        triangle->addComponent(transform);
        transform->matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.7f, 0.7f, 0.0f));
    }
    scene->addObject(triangle);

    auto square = make_shared<Object>();
    {
        auto graphics = make_shared<GraphicsComponent>(square.get());
        square->addComponent(graphics);
        graphics->vertices = {
            -0.5f,  0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
        };

        auto transform = make_shared<TransformComponent>(square.get());
        square->addComponent(transform);
        transform->matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.7f, -0.7f, 0.0f));
    }
    scene->addObject(square);

    return scene;
}

int main(int argc, char** argv) {
    Parameters params(argc, argv);
    Engine instance(params);
    instance.setScene(buildSmallDemoScene());
    instance.start();
}