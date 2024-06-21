/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Mouse.hpp
*/

#pragma once
#include <memory>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

namespace raylib {

    class Mouse {
    public:
        static bool isMouseButtonDown(int button);
        static float getMouseWheelMove();
        static void disableCursor();
    };

} // raylib
