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
#include "../connection/Client.hpp"

class Button {
public:
    enum ButtonState {
        BUTTON,
        BUTTON_OFF
    };

    Button() = default;
    Button(const std::string &text, const std::string &textOff, sf::Vector2f position, std::shared_ptr<sf::Font> &globalFont);

    ~Button() = default;

    void changeTexture();
    void draw(sf::RenderWindow &window);

    std::string getTextureButtonPath() { return _textureButtonPath; }

    std::string getTextureButtonOffPath() { return _textureButtonOffPath; }

    sf::Sprite _sprite;
    sf::Text _text;
    sf::Text _textOn;
    sf::Text _textOff;
    ButtonState _state;
private:
    sf::Vector2f _position;
    sf::Texture _texture;
    std::string _textureButtonPath = "./gui/resources/Button.png";
    std::string _textureButtonOffPath = "./gui/resources/ButtonOff.png";
    sf::Font _font;
    std::string _fontPath = "./gui/resources/font.ttf";
};


class Window {
public:
    Window();
    ~Window();

    void run(Parameters &params, const gui::Client& client);

    void getEvent(Parameters &params);

    void rendMap(Parameters &params);
    void clearMap() { _map.clear(); }

    bool isOpen() { return _window.isOpen(); }

    void displayInformation(const std::shared_ptr<Case>& selectedCase, Parameters &params);
    void addComponentsModal(const std::shared_ptr<Case> &selectedCase, std::shared_ptr<Modal> &modal);

    void displayPlayerInformation(Parameters &params);
    void addPlayerInformation(const std::shared_ptr<Player> &player, std::shared_ptr<Modal> &modal);
    void changePlayer(Parameters &params, int dir);

    unsigned int getWindowWidth() { return _window.getSize().x; }
    unsigned int getWindowHeight() { return _window.getSize().y; }

private:
    std::shared_ptr<sf::Font> _globalFont;
    sf::RenderWindow _window;
    std::deque<std::shared_ptr<sf::RectangleShape>> _map;
    std::unordered_map<std::string, std::shared_ptr<Modal>> _modals;
    int _selectedPlayer = -1;
    std::shared_ptr<Button> _hideEggsButton{};
};
