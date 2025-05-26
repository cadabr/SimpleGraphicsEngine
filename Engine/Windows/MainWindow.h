#pragma once
#include "Windows/Mouse.h"

class MainWindowImpl;

enum class MainWindowState {
    Active,
    DestroyPending
};

class MainWindow {
public:
public:
    MainWindow(const std::string& caption, size_t width, size_t height);
    ~MainWindow();
    std::any to_any() const;
    MainWindowState pollEvents();
    const Mouse& getMouse() const { return mouse; }
    size_t getWidth() const { return width; }
    size_t getHeight() const { return height; }
    float getAspectRatio() const { return height > 0u ? float(width) / float(height) : 1.0f; }
private:
    size_t width;
    size_t height;
    std::string caption;
    Mouse mouse;
    std::unique_ptr<MainWindowImpl> impl;
    friend class MainWindowImpl;
};
