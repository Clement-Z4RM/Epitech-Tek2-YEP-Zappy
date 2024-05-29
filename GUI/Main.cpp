/*
** EPITECH PROJECT, 2024
** Epitech-Tek2-YEP-Zappy
** File description:
** Main.cpp
*/

#include "src/Renderer.hpp"

int main() {
    gui::Renderer renderer(12);

    while (renderer.isOpen()) {
        renderer.handleEvent();
        renderer.clearWindow();
        renderer.drawWindow();
    }
    return 0;
}
