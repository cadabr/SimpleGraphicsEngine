#pragma once

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
    std::unique_ptr<MainWindowImpl> impl;
};
