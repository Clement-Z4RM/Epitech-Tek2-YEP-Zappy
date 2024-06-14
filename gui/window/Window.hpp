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
#include <deque>
#include <memory>
#include <iostream>
#include "../Parameters.hpp"
#include "Modal.hpp"

class Window {
public:
    Window();
    ~Window();

    void run(Parameters &params);

    void getEvent(Parameters &params);

    void rendMap(Parameters &params);
    void clearMap() { _map.clear(); }

    bool isOpen() { return _window.isOpen(); }

    void displayInformation(std::shared_ptr<Case> selectedCase);

private:
    std::shared_ptr<sf::Font> _globalFont;
    sf::RenderWindow _window;
    std::deque<std::shared_ptr<sf::RectangleShape>> _map;
    std::deque<std::shared_ptr<Modal>> _modals;
};
