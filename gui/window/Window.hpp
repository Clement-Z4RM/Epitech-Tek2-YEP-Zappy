/*
** EPITECH PROJECT, 2024
** Epitech_Tek2_YEP_Zappy
** File description:
** Window.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "../Parameters.hpp"

class Window {
public:
    Window();
    ~Window();

    void run();

    void rendMap(Parameters &params);

    void clearMap() { _map.clear(); }
    bool isOpen() { return _window.isOpen(); }

private:
    sf::RenderWindow _window;
    std::deque<std::shared_ptr<sf::RectangleShape>> _map;
};
