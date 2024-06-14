/*
** EPITECH PROJECT, 2024
** Epitech_Tek2_YEP_Zappy
** File description:
** Window.cpp
*/

#include "Window.hpp"

Window::Window()
{
    _window.create(sf::VideoMode(1920, 1080), "Zappy");
    sf::Image *icon = new sf::Image();
    if (icon->loadFromFile("./ressources/empire_nexus.jpeg"))
        _window.setIcon(1024, 1024, icon->getPixelsPtr());
}

Window::~Window() = default;

void Window::run()
{
    if (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
        }
        _window.clear();
        for (auto &i : _map) {
            _window.draw(*i);
        }
        _window.display();
    }
}

void Window::rendMap(Parameters &params)
{
    for (auto &i : params._map) {
        std::shared_ptr<sf::RectangleShape> new_rect = std::make_shared<sf::RectangleShape>();
        if (params.getPlayerOnCase(i).empty())
            new_rect->setFillColor(sf::Color(85,107,47, 255));
        else
            new_rect->setFillColor(sf::Color(255, 99, 71, 255));
        new_rect->setSize(sf::Vector2f(32, 32));
        new_rect->setPosition(i->_x * 32 + 32, i->_y * 32 + 32);
        new_rect->setOutlineColor(sf::Color(128, 128, 128, 255));
        new_rect->setOutlineThickness(1);
        _map.push_back(new_rect);
    }
}
