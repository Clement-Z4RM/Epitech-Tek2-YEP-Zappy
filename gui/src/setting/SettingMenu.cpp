/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** SettingMenu.cpp
*/

#include "SettingMenu.hpp"

Button::Button(const std::string& text, sf::Vector2f position, ButtonState state)
{
    _font.loadFromFile(_fontPath);
    _text.setString(text);
    _text.setCharacterSize(60);
    _text.setFillColor(sf::Color::Black);
    _text.setFont(_font);
    _text.setPosition(position.x + 40, position.y + 35);
    _text.setStyle(sf::Text::Bold);
    _position = position;
    if (state == BUTTON)
        _texture.loadFromFile(_textureButtonPath);
    else if (state == BUTTON_OFF)
        _texture.loadFromFile(_textureButtonOffPath);
    else if (state == BUTTON_CLICK)
        _texture.loadFromFile(_textureButtonClickPath);
    _sprite.setTexture(_texture);
    _sprite.setPosition(_position);
    _state = state;
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
    auto button = std::make_shared<Button>("Connect", sf::Vector2f(1000, 100), Button::BUTTON_OFF);
    _buttons.push_back(button);
    button = std::make_shared<Button>("Quit", sf::Vector2f(1000, 200), Button::BUTTON_OFF);
    _buttons.push_back(button);
    button = std::make_shared<Button>("Settings", sf::Vector2f(1000, 300), Button::BUTTON_OFF);
    _buttons.push_back(button);
}

void SettingMenu::checkClick(sf::RenderWindow &window, sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            for (auto &button : _buttons) {
                if (button->_sprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    button->changeTexture(button->getTextureButtonClickPath());
                else {
                    button->changeTexture(button->getTextureButtonPath());
                }
            }
        }
    }
}
