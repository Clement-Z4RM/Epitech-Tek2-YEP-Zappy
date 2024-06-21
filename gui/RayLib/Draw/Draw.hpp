/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Draw.hpp
*/

#pragma once
#include "Rectangle.hpp"
#include "Cube.hpp"
#include "Draw.hpp"
#include "Text.hpp"

namespace raylib {
    class Draw {
    public:
        static void beginDrawing();
        static void endDrawing();
    };
} // raylib
