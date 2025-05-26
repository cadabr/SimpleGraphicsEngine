#include "pch.h"
#include "Scene/Scene.h"
#include "Scene/Subsystems/GraphicsSubsystem.h"

using glm::value_ptr;
using std::any;
using std::any_cast;

class GraphicsSubsystemImpl {
public:
    GraphicsSubsystemImpl(GraphicsSubsystem& interface, any mainWindow);
    void tick();
private:
    void drawScene();
    void drawDebugInfo();
private:
    GraphicsSubsystem& interface;
    SDL_Window* targetWindow;
};

GraphicsSubsystemImpl::GraphicsSubsystemImpl(GraphicsSubsystem& interface, any mainWindow)
: interface(interface)
, targetWindow(static_cast<SDL_Window*>(any_cast<void*>(mainWindow))) {
}

void GraphicsSubsystemImpl::tick() {
    int width = 0, height = 0;
    SDL_GetWindowSize(targetWindow, &width, &height);
    float aspect = width / float(height);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // TDEBT
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(value_ptr(interface.scene.getCamera()->getProjectionMatrix()));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(value_ptr(interface.scene.getCamera()->getViewMatrix()));
    
    glEnableClientState(GL_VERTEX_ARRAY);
    drawScene();
    drawDebugInfo();
    glDisableClientState(GL_VERTEX_ARRAY);

    SDL_GL_SwapWindow(targetWindow);
}

void GraphicsSubsystemImpl::drawScene() {
    glColor3f(1.0f, 0.0f, 0.0f); // TDEBT

    auto [beginSolid, endSolid] = interface.scene.rangeForComponent<ComponentType::Graphics>();
    for (auto it = beginSolid; it != endSolid; ++it) {
        const auto& vertices = (*it)->getComponent<GraphicsComponent>()->vertices;
        const auto& matrix   = (*it)->getComponent<TransformComponent>()->matrix;

        glPushMatrix();
        glMultMatrixf(value_ptr(matrix));
        glVertexPointer(3, GL_FLOAT, 0, vertices.data());
        glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
        glPopMatrix();
    }
}

void GraphicsSubsystemImpl::drawDebugInfo() {
    auto [beginSolid, endSolid] = interface.scene.rangeForComponent<ComponentType::Collision>();
    for (auto it = beginSolid; it != endSolid; ++it) {
        auto shpereRadius = (*it)->getComponent<CollisionComponent>()->shpereRadius;
        const auto& matrix   = (*it)->getComponent<TransformComponent>()->matrix;

        glPushMatrix();
        glMultMatrixf(value_ptr(matrix));
        GLUquadric* quad = gluNewQuadric();
        gluQuadricDrawStyle(quad, GLU_LINE);
        gluSphere(quad, shpereRadius, 20, 20);
        gluDeleteQuadric(quad);
        glPopMatrix();
    }
}

GraphicsSubsystem::GraphicsSubsystem(Scene& scene)
: Subsystem(scene)
, impl(make_unique<GraphicsSubsystemImpl>(*this, scene.getMainWindowAbstractWrapper())) {
}

GraphicsSubsystem::~GraphicsSubsystem() = default;

void GraphicsSubsystem::tick() {
    impl->tick();
}
