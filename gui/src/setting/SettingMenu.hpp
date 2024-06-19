/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** SettingMenu.hpp
*/

#ifndef ZAPPY_GUI_SETTINGMENU_HPP
#define ZAPPY_GUI_SETTINGMENU_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

class Button {
public:
    Button(const std::string& text, sf::Vector2f position);
    ~Button() = default;
    sf::Sprite _sprite;
    sf::Text _text;
private:
    sf::Vector2f _position;
    sf::Texture _texture;
    std::string _texturePath = "./resources/Button.png";
};

class SettingMenu {
public:
    SettingMenu();
    ~SettingMenu() = default;
    void createButtons();
    void displayButtons(sf::RenderWindow &window);
    void displaySettingMenu(sf::RenderWindow &window);
private:
    std::vector<std::shared_ptr<Button>> _buttons;
};

#endif //ZAPPY_GUI_SETTINGMENU_HPP
