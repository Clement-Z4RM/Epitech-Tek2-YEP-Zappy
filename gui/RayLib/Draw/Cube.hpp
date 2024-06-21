/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Cube.hpp
*/

#pragma once
#include <memory>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

namespace raylib {

    class Cube {
    public:
        static void drawCube(Vector3 position, float width, float height, float length, Color color);
        static void drawCubeWires(Vector3 position, float width, float height, float length, Color color);
    };

} // raylib
