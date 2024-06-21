//
// Created by mzucchero on 6/21/24.
//

#include "Mouse.hpp"

namespace raylib {

    bool Mouse::isMouseButtonDown(int button) {
        return IsMouseButtonDown(button);
    }

    float Mouse::getMouseWheelMove() {
        return GetMouseWheelMove();
    }

    void Mouse::disableCursor() {
        DisableCursor();
    }

} // raylib