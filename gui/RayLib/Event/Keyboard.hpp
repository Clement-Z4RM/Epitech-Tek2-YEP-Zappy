//
// Created by mzucchero on 6/21/24.
//

#pragma once
#include <memory>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

namespace raylib {

    class Keyboard {
    public:
        static bool isKeyPressed(int key);
    };

} // raylib
