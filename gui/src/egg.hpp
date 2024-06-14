/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** egg.hpp
*/

#pragma once

#include <iostream>
#include <sstream>
#include <vector>

class Egg {
public:
    Egg() = default;
    Egg(int id, int x, int y);
    ~Egg() = default;

    int _id;
    int _x;
    int _y;
};

class Eggs {
public:
    Eggs() = default;
    ~Eggs() = default;
    void addEgg(int id, int x, int y);
    void deleteEgg(int id);
    bool checkMsg(std::string &s);

private:
    std::vector<Egg> _eggs;
    static bool startsWith(const std::string& str, const std::string& prefix);
};
