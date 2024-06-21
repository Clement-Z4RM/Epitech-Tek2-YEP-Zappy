//
// Created by mzucchero on 6/21/24.
//

#include "Keyboard.hpp"

namespace raylib {

    bool Keyboard::isKeyPressed(int key) {
        return IsKeyPressed(key);
    }

} // raylib