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
#include "../../connection/Client.hpp"
namespace gui {
    class Button {
    public:
        enum ButtonState {
            BUTTON,
            BUTTON_OFF,
            BUTTON_CLICK
        };
        enum ButtonType {
            TeamName,
            PlayerLevel,
            PlayerPosition,
            PlayerInventory,
            TimeUnitRequest,
            TimeUnitMod
        };

        Button(const std::string &text, sf::Vector2f position, ButtonType type,
               ButtonState state = BUTTON);

        ~Button() = default;

        void changeTexture(const std::string& texturePath);

        std::string getTextureButtonPath() { return _textureButtonPath; }

        std::string getTextureButtonOffPath() { return _textureButtonOffPath; }

        std::string
        getTextureButtonClickPath() { return _textureButtonClickPath; }

        ButtonType getType() { return _type; }

        void buttonPushed(Client &client);

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
        ButtonType _type;
    };

    class SettingMenu {
    public:
        SettingMenu();

        ~SettingMenu() = default;

        void createButtons();

        void displayButtons(sf::RenderWindow &window);

        void displaySettingMenu(sf::RenderWindow &window);

        void checkClick(sf::RenderWindow &window, Client client);

    private:
        std::vector<std::shared_ptr<Button>> _buttons;
        std::vector<std::shared_ptr<std::string>> _teamsNames;
        std::vector<std::shared_ptr<std::string>> _playerDetails;
    };
}

#endif //ZAPPY_GUI_SETTINGMENU_HPP
