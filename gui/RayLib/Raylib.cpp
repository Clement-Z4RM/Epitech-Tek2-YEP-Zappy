/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Raylib.cpp
*/

#include "Raylib.hpp"

namespace raylib {

    void Raylib::initWindow(int width, int height, const char *title) {
        InitWindow(width, height, title);
    }

    void Raylib::setFPS(int fps) {
        SetTargetFPS(fps);
    }

    bool Raylib::windowShouldClose() {
        return WindowShouldClose();
    }

    void Raylib::clearBackground(Color color) {
        ClearBackground(color);
    }
}
