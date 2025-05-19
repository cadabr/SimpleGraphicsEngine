#pragma once

enum class MouseButtonField {
    Right  = 0,
    Middle = 1,
    Left   = 2
};

using MouseButtonState = std::bitset<3>;

struct MousePosition {
    float horisontal;
    float vertical;
};

struct Mouse {
    MouseButtonState buttons;
    MousePosition position;
};
