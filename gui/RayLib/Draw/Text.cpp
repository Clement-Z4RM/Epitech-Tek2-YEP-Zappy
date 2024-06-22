/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Text.cpp
*/

#include "Text.hpp"

namespace raylib {

    void Text::drawText(std::string &text, int x, int y, int fontSize, Color color) {
        DrawText(text.c_str(), x, y, fontSize, color);
    }

    void Text::drawText(const char *text, int x, int y, int fontSize, Color color) {
        DrawText(text, x, y, fontSize, color);
    }

} // raylib