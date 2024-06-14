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
        addEgg(0, 0, 0);
        return true;
    }
    if (startsWith(str, "edi")) {
        deleteEgg(0);
        return true;
    }
    if (startsWith(str, "eht")) {
        deleteEgg(0);
        return true;
    }
    if (startsWith(str, "pfk")) {
        deleteEgg(0);
        return true;
    }
    if (startsWith(str, "ebo")) {
        deleteEgg(0);
        return true;
    }
    return false;
}

Egg::Egg(int id, int x, int y) : _id(id), _x(x), _y(y) {}

void Eggs::deleteEgg(int id)
{
    for (auto it = _eggs.begin(); it != _eggs.end(); it++) {
        if (it->_id == id) {
            _eggs.erase(it);
            return;
        }
    }
}

void Eggs::addEgg(int id, int x, int y)
{
    _eggs.push_back(Egg(id, x, y));
}

void Eggs::renderEggs()
{
    for (auto &egg : _eggs) {
        std::shared_ptr<sf::Sprite> shape = std::make_shared<sf::Sprite>();
        shape->setPosition(egg._x * 32 + 32, egg._y * 32 + 32);
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
