#include "pch.h"
#include "Windows/MainWindow.h"
#include "Windows/Mouse.h"

using std::any;
using std::array;
using std::make_unique;
using std::move;
using std::string;

class MainWindowImpl {
public:
    MainWindowImpl(MainWindow& mainWindow, const string& caption, size_t width, size_t height);
    ~MainWindowImpl();
    any to_any() const;
    MainWindowState pollEvents();
private:
    MousePosition sdlMouseMotion2Position(const SDL_MouseMotionEvent& motion) const;
private:
    MainWindow& mainWindow;
    SDL_Window* sdl_window;
    SDL_GLContext glContext;
};

MainWindowImpl::MainWindowImpl(MainWindow& mainWindow, const string& caption, size_t width, size_t height)
: mainWindow(mainWindow)
, sdl_window(nullptr)
, glContext(nullptr) {
    SDL_Init(SDL_INIT_VIDEO);
    sdl_window = SDL_CreateWindow(caption.c_str(), mainWindow.width,  mainWindow.height, SDL_WINDOW_OPENGL);
    glContext = SDL_GL_CreateContext(sdl_window);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
}

MainWindowImpl::~MainWindowImpl() {
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

any MainWindowImpl::to_any() const {
    return static_cast<void*>(sdl_window);
}

MainWindowState MainWindowImpl::pollEvents() {
    static array<size_t, 3> SDL_ButtonsRemap {
        static_cast<size_t>( MouseButton::Right  ),
        static_cast<size_t>( MouseButton::Left   ),
        static_cast<size_t>( MouseButton::Middle )
    };

    auto result = MainWindowState::Active;
    SDL_Event event = {};
    while(SDL_PollEvent(&event)) {
        if(SDL_EVENT_QUIT == event.type) {
            result = MainWindowState::DestroyPending;
        } else if(SDL_EVENT_MOUSE_MOTION == event.type) {
            mainWindow.mouse.position = move(sdlMouseMotion2Position(event.motion));
        } else if(SDL_EVENT_MOUSE_BUTTON_DOWN == event.type) {
            mainWindow.mouse.buttons[SDL_ButtonsRemap[event.button.button]] = true;
        } else if(SDL_EVENT_MOUSE_BUTTON_UP == event.type) {
            mainWindow.mouse.buttons[SDL_ButtonsRemap[event.button.button]] = false;
        }
    }
    return result;
}

MousePosition MainWindowImpl::sdlMouseMotion2Position(const SDL_MouseMotionEvent& motion) const {
    MousePosition result{int(motion.x), int(motion.y), motion.x / mainWindow.getWidth(), motion.y / mainWindow.getHeight()};
    return result;
}

MainWindow::MainWindow(const string& caption, size_t width, size_t height)
: impl(make_unique<MainWindowImpl>(*this, caption, width, height))
, caption(caption)
, width(width)
, height(height) {
}

MainWindow::~MainWindow() = default;

any MainWindow::to_any() const {
    return impl->to_any();
}

MainWindowState MainWindow::pollEvents() {
    return impl->pollEvents();
}