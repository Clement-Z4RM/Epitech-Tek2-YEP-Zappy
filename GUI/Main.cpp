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
        sf::Event event;
        if (renderer.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                renderer.getWindow().close();
            }
            if (event.key.code == sf::Keyboard::Escape && event.type == sf::Event::KeyReleased) {
                renderer.getWindow().close();
                return 0;
            }
        }
        renderer.clearWindow();
        renderer.drawWindow();
    }
    return 0;
}
