#pragma once
#include "Engine.h"
#include "Subsystem.h"
#include "Components/GraphicsComponent.h"
#include "Components/TransformComponent.h"

class GraphicsSubsystem : public Subsystem {
public:
    GraphicsSubsystem() {
        auto argc = Engine::instance().getParameters().argc;
        auto argv = Engine::instance().getParameters().argv;
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(640, 480);
        glutCreateWindow("GLUT Window");
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glutDisplayFunc(displayCallback);
    }

    void tick() override {
        // glutMainLoopEvent();
        // glutPostRedisplay();
    }

private:
    static void displayCallback() {
        glClear(GL_COLOR_BUFFER_BIT);
        glEnableClientState(GL_VERTEX_ARRAY);
        glMatrixMode(GL_MODELVIEW);

        auto [beginRenderer, endRenderer] = Engine::instance().getScene()->rangeForComponent<ComponentType::Graphics>();
        for (auto it = beginRenderer; it != endRenderer; ++it) {
            const auto& vertices = (*it)->getComponent<GraphicsComponent>()->vertices;
            const auto& matrix   = (*it)->getComponent<TransformComponent>()->matrix;

            glLoadIdentity();
            glLoadMatrixf(matrix.data());
            glVertexPointer(vertices.size(), GL_FLOAT, 0, vertices.data());
            glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
        }

        glDisableClientState(GL_VERTEX_ARRAY);
        glutSwapBuffers();
    }
};
