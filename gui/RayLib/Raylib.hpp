/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Raylib.hpp
*/

#pragma once
#include <memory>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "Camera/Camera.hpp"
#include "Draw/Draw.hpp"
#include "Event/Event.hpp"

namespace raylib {

    class Raylib {
    public:
        static void initWindow(int width, int height, const char *title);
        static bool windowShouldClose();

        static void setFPS(int fps);

        static void clearBackground(Color color);

    };

}