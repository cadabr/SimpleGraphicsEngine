#include "pch.h"
#include "Scene/Components/GraphicsComponent.h"
#include "Scene/Components/TransformComponent.h"
#include "GraphicsSubsystem.h"
#include "Scene/Scene.h"

using glm::value_ptr;
using std::any;
using std::any_cast;

class GraphicsSubsystemImpl {
public:
    GraphicsSubsystemImpl(any mainWindow);
    void tick(Scene* scene);
private:
    SDL_Window* targetWindow;
};

GraphicsSubsystemImpl::GraphicsSubsystemImpl(any mainWindow)
: targetWindow(static_cast<SDL_Window*>(any_cast<void*>(mainWindow))) {
}

void GraphicsSubsystemImpl::tick(Scene* scene) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glMatrixMode(GL_MODELVIEW);

    auto [beginRenderer, endRenderer] = scene->rangeForComponent<ComponentType::Graphics>();
    for (auto it = beginRenderer; it != endRenderer; ++it) {
        const auto& vertices = (*it)->getComponent<GraphicsComponent>()->vertices;
        const auto& matrix   = (*it)->getComponent<TransformComponent>()->matrix;

        glLoadIdentity();
        glLoadMatrixf(value_ptr(matrix));
        glVertexPointer(3, GL_FLOAT, 0, vertices.data());
        glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
    }

    glDisableClientState(GL_VERTEX_ARRAY);

    SDL_GL_SwapWindow(targetWindow);
}

GraphicsSubsystem::GraphicsSubsystem(any window)
: impl(make_unique<GraphicsSubsystemImpl>(window)) {
}

GraphicsSubsystem::~GraphicsSubsystem() = default;

void GraphicsSubsystem::tick(Scene* scene) {
    impl->tick(scene);
}
