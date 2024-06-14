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
#include <unordered_map>
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

    void displayInformation(const std::shared_ptr<Case>& selectedCase, Parameters &params);
    void addComponentsModal(const std::shared_ptr<Case> &selectedCase, std::shared_ptr<Modal> &modal);

private:
    std::shared_ptr<sf::Font> _globalFont;
    sf::RenderWindow _window;
    std::deque<std::shared_ptr<sf::RectangleShape>> _map;
    std::unordered_map<std::string, std::shared_ptr<Modal>> _modals;
};
