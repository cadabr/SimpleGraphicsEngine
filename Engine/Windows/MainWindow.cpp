#include "pch.h"
#include "MainWindow.h"

using std::any;
using std::make_unique;

class MainWindowImpl {
public:
    MainWindowImpl();
    ~MainWindowImpl();
    any to_any() const;
    MainWindowState pollEvents();
private:
    SDL_Window* window;
    SDL_GLContext glContext;
};

MainWindowImpl::MainWindowImpl()
: window(nullptr)
, glContext(nullptr) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Main Window", 1024, 768, SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(window);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
}

MainWindowImpl::~MainWindowImpl() {
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

any MainWindowImpl::to_any() const {
    return static_cast<void*>(window);
}

MainWindowState MainWindowImpl::pollEvents() {
    auto result = MainWindowState::Active;
    /*SDL_Event event = {};
    while(SDL_PollEvent(&event)) {
        if(SDL_EVENT_QUIT == event.type) {
            result = MainWindowState::DestroyPending;
        }
    }*/
    return result;
}

MainWindow::MainWindow()
: impl(make_unique<MainWindowImpl>()) {
}

MainWindow::~MainWindow() = default;

any MainWindow::to_any() const {
    return impl->to_any();
}

MainWindowState MainWindow::pollEvents() {
    return impl->pollEvents();
}