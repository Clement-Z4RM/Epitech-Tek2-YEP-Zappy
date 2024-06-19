/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** SettingMenu.cpp
*/

#include "SettingMenu.hpp"

Button::Button(const std::string& text, sf::Vector2f position)
{
    _text.setString(text);
    _position = position;
    _texture.loadFromFile(_texturePath);
    _sprite.setTexture(_texture);
    _sprite.setPosition(_position);
}

SettingMenu::SettingMenu()
{
    createButtons();
}

void SettingMenu::displayButtons(sf::RenderWindow &window)
{
    for (auto &button : _buttons) {
        window.draw(button->_sprite);
        window.draw(button->_text);
    }
}

void SettingMenu::displaySettingMenu(sf::RenderWindow &window)
{
    displayButtons(window);
}

void SettingMenu::createButtons()
{
    auto button = std::make_shared<Button>("Connect", sf::Vector2f(100, 100));
    _buttons.push_back(button);
}
