#pragma once
#include "Mouse.h"

class MainWindowImpl;

enum class MainWindowState {
    Active,
    DestroyPending
};

class MainWindow {
public:
public:
    MainWindow();
    ~MainWindow();
    std::any to_any() const;
    MainWindowState pollEvents();
private:
    Mouse mouse;
    std::unique_ptr<MainWindowImpl> impl;

    friend class MainWindowImpl;
};
