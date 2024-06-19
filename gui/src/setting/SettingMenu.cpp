/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** SettingMenu.cpp
*/

#include "SettingMenu.hpp"

Button::Button(const std::string& text, sf::Vector2f position)
{
    _font.loadFromFile(_fontPath);
    _text.setString(text);
    _text.setCharacterSize(60);
    _text.setFillColor(sf::Color::Black);
    _text.setFont(_font);
    _text.setPosition(position.x + 40, position.y + 35);
    _text.setStyle(sf::Text::Bold);
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
    auto button = std::make_shared<Button>("Connect", sf::Vector2f(1000, 100));
    _buttons.push_back(button);
}
