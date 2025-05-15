#include "pch.h"
#include "Scene/Components/GraphicsComponent.h"
#include "Scene/Components/TransformComponent.h"
#include "GraphicsSubsystem.h"
#include "Scene/Scene.h"

using glm::value_ptr;

class GraphicsSubsystemImpl {
public:
    GraphicsSubsystemImpl();
    ~GraphicsSubsystemImpl();
    void tick(Scene* scene);
private:
    SDL_Window* window = nullptr;
    SDL_GLContext glContext = nullptr;
};

GraphicsSubsystemImpl::GraphicsSubsystemImpl() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("My Window", 1024, 768, SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(window);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
}

GraphicsSubsystemImpl::~GraphicsSubsystemImpl() {
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
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

    SDL_GL_SwapWindow(window);
}

GraphicsSubsystem::GraphicsSubsystem()
: impl(std::make_unique<GraphicsSubsystemImpl>()) {
}

GraphicsSubsystem::~GraphicsSubsystem() = default;

void GraphicsSubsystem::tick(Scene* scene) {
    impl->tick(scene);
}
