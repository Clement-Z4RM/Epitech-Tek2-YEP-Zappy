/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Grid.cpp
*/

#include "Grid.hpp"
#include <memory>
#include <string>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

namespace raylib {

    void Grid::drawGrid(int slices, float spacing) {
        DrawGrid(slices, spacing);
    }

} // raylib