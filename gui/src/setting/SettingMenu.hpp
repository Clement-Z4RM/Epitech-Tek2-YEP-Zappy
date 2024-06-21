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
    enum ButtonState {
        BUTTON,
        BUTTON_OFF,
        BUTTON_CLICK
    };
    Button(const std::string& text, sf::Vector2f position, ButtonState state);
    ~Button() = default;
    void changeTexture(std::string texturePath) { _texture.loadFromFile(texturePath); _sprite.setTexture(_texture); }
    std::string getTextureButtonPath() { return _textureButtonPath; }
    std::string getTextureButtonOffPath() { return _textureButtonOffPath; }
    std::string getTextureButtonClickPath() { return _textureButtonClickPath; }
    sf::Sprite _sprite;
    sf::Text _text;
private:
    sf::Vector2f _position;
    sf::Texture _texture;
    std::string _textureButtonPath = "./resources/Button.png";
    std::string _textureButtonOffPath = "./resources/ButtonOff.png";
    std::string _textureButtonClickPath = "./resources/ButtonClick.png";
    sf::Font _font;
    std::string _fontPath = "./resources/font.ttf";
    ButtonState _state;
};

class SettingMenu {
public:
    SettingMenu();
    ~SettingMenu() = default;
    void createButtons();
    void displayButtons(sf::RenderWindow &window);
    void displaySettingMenu(sf::RenderWindow &window);
    void checkClick(sf::RenderWindow &window, sf::Event &event);
private:
    std::vector<std::shared_ptr<Button>> _buttons;
    std::vector<std::shared_ptr<std::string>> _teamsNames;
    std::vector<std::shared_ptr<std::string>> _playerDetails;
};

#endif //ZAPPY_GUI_SETTINGMENU_HPP
