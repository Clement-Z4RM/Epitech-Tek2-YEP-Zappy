/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Rectangle.cpp
*/

#include "Rectangle.hpp"

void raylib::Rectangle::drawRectangle(int x, int y, int width, int height, Color color) {
    DrawRectangle(x, y, width, height, color);
}

void raylib::Rectangle::drawRectangleLines(int x, int y, int width, int height, Color color) {
    DrawRectangleLines(x, y, width, height, color);
}
