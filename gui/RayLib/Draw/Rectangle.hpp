/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Rectangle.hpp
*/

#pragma once
#include <memory>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

namespace raylib {
    class Rectangle {
    public:
        static void drawRectangle(int x, int y, int width, int height, Color color);

        static void drawRectangleLines(int x, int y, int width, int height, Color color);

    };
}
