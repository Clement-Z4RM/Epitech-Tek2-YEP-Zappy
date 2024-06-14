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
    _globalFont = std::make_shared<sf::Font>();
    if (!_globalFont->loadFromFile("./ressources/font.ttf"))
        std::cerr << "Error loading font" << std::endl;
}

Window::~Window() = default;

void Window::run(Parameters &params)
{
    if (_window.isOpen()) {
        getEvent(params);
        _window.clear();
        for (auto &i : _map) {
            _window.draw(*i);
        }
        for (auto &i : _modals) {
            i->display(_window);
        }
        _window.display();
    }
}

void Window::getEvent(Parameters &params)
{
    sf::Event event;

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                int index = 0;
                bool found = false;
                for (auto &i : _map) {
                    if (i->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        auto it = params._map[index];
                        displayInformation(it);
                        found = true;
                        break;
                    }
                    index++;
                }
                if (!found)
                    _modals.clear();
            }
        }
    }
}

void Window::displayInformation(std::shared_ptr<Case> selectedCase)
{
    std::shared_ptr<Modal> modal = std::make_shared<Modal>();
    std::shared_ptr<sf::Text> text = std::make_shared<sf::Text>();
    std::string str = "Case: " + std::to_string(selectedCase->_x) + " " + std::to_string(selectedCase->_y) + "\n";
    str += "Food: " + std::to_string(selectedCase->_food) + "\n";
    str += "Linemate: " + std::to_string(selectedCase->_linemate) + "\n";
    str += "Deraumere: " + std::to_string(selectedCase->_deraumere) + "\n";
    str += "Sibur: " + std::to_string(selectedCase->_sibur) + "\n";
    str += "Mendiane: " + std::to_string(selectedCase->_mendiane) + "\n";
    str += "Phiras: " + std::to_string(selectedCase->_phiras) + "\n";
    str += "Thystame: " + std::to_string(selectedCase->_thystame) + "\n";
    text->setString(str);
    text->setCharacterSize(20);
    text->setFont(*_globalFont);
    text->setPosition(_window.getSize().x * 0.75 + 10, 75);
    modal->addText(text);
    modal->setPosition(_window.getSize().x * 0.75, 50);
    modal->setSize(_window.getSize().x * 0.20, _window.getSize().y - 100);
    modal->setColor(100, 20, 20, 255);
    _modals.clear();
    _modals.push_back(modal);
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
