/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Player.hpp
*/

#pragma once
#include <sstream>

enum Orientation {
    NORTH = 1,
    EAST = 2,
    SOUTH = 3,
    WEST = 4
};

class Coordinates {
public:
    Coordinates() = default;
    Coordinates(int x, int y) : _x(x), _y(y) {};
    ~Coordinates() = default;

    int _x;
    int _y;
};

class Inventory {
public:
    Inventory() = default;
    Inventory(int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame) :
    _food(food), _linemate(linemate), _deraumere(deraumere), _sibur(sibur), _mendiane(mendiane), _phiras(phiras), _thystame(thystame) {};
    ~Inventory() = default;

    int _food;
    int _linemate;
    int _deraumere;
    int _sibur;
    int _mendiane;
    int _phiras;
    int _thystame;

};

class Player {
public:
    Player() = default;
    explicit Player(std::stringstream &s);
    ~Player() = default;

    void setLevel(int level) { _level = level; }
    void setOrientation(Orientation orientation) { _orientation = orientation; }
    void setPosition(int x, int y) { _position._x = x; _position._y = y; }

    void setInventory(std::stringstream  &s);
    void setInventory(int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame) { _inventory = Inventory(food, linemate, deraumere, sibur, mendiane, phiras, thystame); }

    int getLevel() { return _level; }
    Orientation getOrientation() { return _orientation; }
    Coordinates getPosition() { return _position; }
    Inventory getInventory() { return _inventory; }
    int getId() { return _id; }

private:
    Coordinates _position{};
    Orientation _orientation;
    int _level;
    int _id;
    std::string _team;
    Inventory _inventory{};
};