/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Text.hpp
*/

#pragma once
#include <memory>
#include <string>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

namespace raylib {

    class Text {
    public:
        static void drawText(std::string &text, int x, int y, int fontSize, Color color);
        static void drawText(const char *text, int x, int y, int fontSize, Color color);
    };

} // raylib
