/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Player.cpp
*/

#include "Player.hpp"

Player::Player(std::stringstream &s)
{
    std::string str;
    s >> str;
    s >> str;
    _id = std::stoi(str);
    s >> str;
    _position._x = std::stoi(str);
    s >> str;
    _position._y = std::stoi(str);
    s >> str;
    _orientation = static_cast<Orientation>(std::stoi(str));
    s >> str;
    _level = std::stoi(str);
    s >> str;
    _team = str;
}

void Player::setInventory(std::stringstream &s)
{
    std::string str;
    s >> str;
    s >> str;
    _inventory._food = std::stoi(str);
    s >> str;
    _inventory._linemate = std::stoi(str);
    s >> str;
    _inventory._deraumere = std::stoi(str);
    s >> str;
    _inventory._sibur = std::stoi(str);
    s >> str;
    _inventory._mendiane = std::stoi(str);
    s >> str;
    _inventory._phiras = std::stoi(str);
    s >> str;
    _inventory._thystame = std::stoi(str);
}
