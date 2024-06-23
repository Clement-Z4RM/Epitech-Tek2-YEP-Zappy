/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** egg.cpp
*/

#include "egg.hpp"

Eggs::Eggs()
{
    _eggTexture.loadFromFile(_eggTexturePath);
    _eggButton = std::make_shared<Button>("Eggs", sf::Vector2f(1500, 900));
}

bool Eggs::startsWith(const std::string &str, const std::string &prefix)
{
    return str.compare(0, prefix.size(), prefix) == 0;
}

bool Eggs::checkMsg(std::string &s)
{
    std::stringstream ss(s);
    std::string str;
    ss >> str;
    if (startsWith(str, "enw")) {
        std::vector <std::string> tab = splitStr(s, ' ');
        int id = std::stoi(tab[1]);
        int team = std::stoi(tab[2]);
        int x = std::stoi(tab[3]);
        int y = std::stoi(tab[4]);
        addEgg(id, team, x, y);
        return true;
    }
    if (startsWith(str, "edi")) {
        deleteEgg(0);
        return true;
    }
    if (startsWith(str, "pfk")) {
        layingEgg(s);
        return true;
    }
    if (startsWith(str, "ebo")) {
        newConnection(s);
        return true;
    }
    if (startsWith(str, "eht")) {
        eggHatching(s);
        return true;
    }
    return false;
}

Egg::Egg(int id, int team, int x, int y) : _id(id), _x(x), _y(y), _team(team) {}

void Eggs::deleteEgg(int id)
{
    std::vector<std::shared_ptr<Egg>> tmp;
    for (auto egg : _eggs) {
        int eggId = egg->getId();
        if (eggId == id)
            continue;
        else
            tmp.push_back(egg);
    }
    _eggs = tmp;
}

void Eggs::addEgg(int id,int team, int x, int y)
{
    std::shared_ptr<Egg> new_egg = std::make_shared<Egg>(id, team, x, y);
    _eggs.push_back(new_egg);
    _nbEggsCreated++;
}

void Eggs::renderEggs(int width, int height, int mapWidth, int mapHeight)
{
    _eggsShapes.clear();
    float squareSize = (width * 0.9 / mapWidth) < (height * 0.9 / mapHeight) ? (width * 0.9 / mapWidth) : (height * 0.9 / mapHeight);
    float scale = squareSize / 32;
    for (auto &egg : _eggs) {
        int posX = egg->_x * squareSize + width * 0.5 / 2;
        int posY = egg->_y * squareSize + height * 0.1 / 2;
        std::shared_ptr<sf::Sprite> shape = std::make_shared<sf::Sprite>();
        shape->setPosition(posX, posY);
        shape->setScale(scale, scale);
        shape->setTexture(_eggTexture);
        _eggsShapes.push_back(shape);
    }
}

std::vector<std::string> Eggs::splitStr(const std::string &str, char delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string tok;

    while (getline(ss, tok, delimiter)) {
        result.push_back(tok);
    }
    return result;
}

void Eggs::layingEgg(std::string &msg)
{
    std::vector<std::string> tab = splitStr(msg, ' ');
    int id = std::stoi(tab[1]);
    for (auto &egg : _eggs) {
        if (egg->getId() == id) {
            egg->setIsLaying(true);
            return;
        }
    }
}

void Eggs::newConnection(std::string &msg)
{
    std::vector<std::string> tab = splitStr(msg, ' ');
    int id = std::stoi(tab[1]);
    for (auto &egg : _eggs) {
        if (egg->getId() == id) {
            this->deleteEgg(id);
            return;
        }
    }
}

void Eggs::eggHatching(std::string &msg)
{
    std::vector<std::string> tab = splitStr(msg, ' ');
    int id = std::stoi(tab[1]);
    for (auto &egg : _eggs) {
        if (egg->getId() == id) {
            egg->setIsLaying(false);
            return;
        }
    }
}

void Eggs::checkClick(sf::RenderWindow &window)
{
    sf::Event event{};
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left)
                if (_eggButton->_sprite.getGlobalBounds().contains(
                        window.mapPixelToCoords(
                                sf::Mouse::getPosition(window))))
                    _eggButton->changeTexture();
        }
}

void Eggs::displayEggs(sf::RenderWindow &window)
{
    window.draw(_eggButton->_sprite);
    window.draw(_eggButton->_text);
    checkClick(window);
    if (_eggButton->_state == Button::BUTTON_OFF)
        return;
    for (auto &egg : _eggsShapes) {
        window.draw(*egg);
    }
}

Button::Button(const std::string &text, sf::Vector2f position) {
    _state = BUTTON;
    _font.loadFromFile(_fontPath);
    _text.setString(text);
    _text.setCharacterSize(60);
    _text.setFillColor(sf::Color::Black);
    _text.setFont(_font);
    _text.setPosition(position.x + 40, position.y + 35);
    _text.setStyle(sf::Text::Bold);
    _position = position;
    _texture.loadFromFile(_textureButtonPath);
    _sprite.setTexture(_texture);
    _sprite.setPosition(_position);
}

void Button::changeTexture()
{
    if (_state == BUTTON)
        _texture.loadFromFile(_textureButtonPath);
    else if (_state == BUTTON_OFF)
        _texture.loadFromFile(_textureButtonOffPath);
}
