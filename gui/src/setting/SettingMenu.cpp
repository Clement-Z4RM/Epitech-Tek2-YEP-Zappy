/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** SettingMenu.cpp
*/

#include "SettingMenu.hpp"
namespace gui {
    Button::Button(const std::string &text, sf::Vector2f position,
                   ButtonType type, ButtonState state) {
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

    void Button::buttonPushed(Client &client) {
        if (_type == TeamName) {
            std::cout << "Team name button pushed" << std::endl;
            std::string msg = "tna\n";
            client.sendMsg(msg);
        } else if (_type == PlayerLevel) {
            std::cout << "Player level button pushed" << std::endl;
            std::string msg = "plv\n";
            client.sendMsg(msg);
        } else if (_type == PlayerPosition) {
            std::cout << "Player position button pushed" << std::endl;
            std::string msg = "ppo\n";
            client.sendMsg(msg);
        } else if (_type == PlayerInventory) {
            std::cout << "Player inventory button pushed" << std::endl;
            std::string msg = "pin\n";
            client.sendMsg(msg);
        } else if (_type == TimeUnitRequest) {
            std::cout << "Time unit request button pushed" << std::endl;
            std::string msg = "sst\n";
            client.sendMsg(msg);
        } else if (_type == TimeUnitMod) {
            std::cout << "Time unit mod button pushed" << std::endl;
            std::string msg = "sgt\n";
            client.sendMsg(msg);
        }
    }

    void Button::changeTexture(const std::string& texturePath)
    {
        _texture.loadFromFile(texturePath);
        _sprite.setTexture(_texture);
    }

    SettingMenu::SettingMenu()
    {
        createButtons();
    }

    void SettingMenu::displayButtons(sf::RenderWindow &window)
    {
        for (auto &button: _buttons) {
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
        auto button = std::make_shared<Button>("Teams name",
                                               sf::Vector2f(1000, 100),
                                               Button::TeamName);
        _buttons.push_back(button);
        button = std::make_shared<Button>("Level", sf::Vector2f(1000, 200),
                                          Button::PlayerLevel);
        _buttons.push_back(button);
        button = std::make_shared<Button>("Position", sf::Vector2f(1000, 300),
                                          Button::PlayerPosition);
        _buttons.push_back(button);
        button = std::make_shared<Button>("Inventory", sf::Vector2f(1000, 400),
                                          Button::PlayerInventory);
        _buttons.push_back(button);
        button = std::make_shared<Button>("Time unit request",
                                          sf::Vector2f(1000, 500),
                                          Button::TimeUnitRequest);
        _buttons.push_back(button);
        button = std::make_shared<Button>("Time unit mod",
                                          sf::Vector2f(1000, 600),
                                          Button::TimeUnitMod);
        _buttons.push_back(button);
    }

    void SettingMenu::checkClick(sf::RenderWindow &window, Client client) {
        sf::Event event{};
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                for (auto &button: _buttons) {
                    if (button->_sprite.getGlobalBounds().contains(
                            window.mapPixelToCoords(
                                    sf::Mouse::getPosition(window))))
                        button->buttonPushed(client);
                    else {
                        button->changeTexture(button->getTextureButtonPath());
                    }
                }
            }
        }
    }
}
