#pragma once

enum class MouseButton {
    Right  = 0,
    Middle = 1,
    Left   = 2
};

using MouseButtonState = std::bitset<3>;

struct MousePosition {
    int pixelWidth;
    int pixelHeight;
    float relativeWidth;
    float relativeHeight;
    // NDC - Normalized Device Coordinates. Обе изменяется в диапозоне [-1.0f, 1.0f]
    float getNdcWidth() const { return 2.0f * relativeWidth - 1.0f; }
    float getNdcHeight() const { return 1.0f - 2.0f * relativeHeight; }
};

struct Mouse {
    MouseButtonState buttons;
    MousePosition position;
    bool isPressed(MouseButton button) const { return buttons[static_cast<size_t>(button)]; }
};
