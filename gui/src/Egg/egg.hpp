/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** egg file
*/

#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <SFML/Graphics.hpp>
#include <memory>

class Button {
public:
    enum ButtonState {
        BUTTON,
        BUTTON_OFF
    };

    Button(const std::string &text, sf::Vector2f position);

    ~Button() = default;

    void changeTexture();

    std::string getTextureButtonPath() { return _textureButtonPath; }

    std::string getTextureButtonOffPath() { return _textureButtonOffPath; }

    sf::Sprite _sprite;
    sf::Text _text;
    ButtonState _state;
private:
    sf::Vector2f _position;
    sf::Texture _texture;
    std::string _textureButtonPath = "./gui/resources/Button.png";
    std::string _textureButtonOffPath = "./gui/resources/ButtonOff.png";
    sf::Font _font;
    std::string _fontPath = "./gui/resources/font.ttf";
};

class Egg {
public:
    Egg(int id, int team, int x, int y);
    ~Egg() = default;
    bool getIsLaying() const { return _isLaying; }
    void setIsLaying(bool isLaying) { _isLaying = isLaying; }
    int getId() const { return _id; }
    int _x;
    int _y;

private:
    bool _isLaying = false;
    int _id;
    int _team;
};

class Eggs {
public:
    Eggs();
    ~Eggs() = default;
    void addEgg(int id,int team, int x, int y);
    void deleteEgg(int id);
    bool checkMsg(std::string &s);
    void renderEggs(int width, int height, int mapWidth, int mapHeight);
    void layingEgg(std::string &msg);
    void newConnection(std::string &msg);
    void eggHatching(std::string &msg);
    void checkClick(sf::RenderWindow &window);
    void displayEggs(sf::RenderWindow &window);
    sf::Sprite getEggButtonSprite() { return _eggButton->_sprite; }
    std::deque<std::shared_ptr<sf::Sprite>> _eggsShapes;
    std::shared_ptr<Button> _eggButton;

private:
    std::vector<std::shared_ptr<Egg>> _eggs;
    static bool startsWith(const std::string& str, const std::string& prefix);
    static std::vector<std::string> splitStr(const std::string &str, char delimiter);
    std::string _eggTexturePath = "./gui/resources/Egg.png";
    sf::Texture _eggTexture;
    int _nbEggsCreated = 0;
};
