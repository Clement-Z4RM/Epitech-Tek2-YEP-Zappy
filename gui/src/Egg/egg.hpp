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
#include <deque>
#include <SFML/Graphics.hpp>
#include <memory>

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
    Eggs();
    ~Eggs() = default;
    void addEgg(int id, int x, int y);
    void deleteEgg(int id);
    bool checkMsg(std::string &s);
    void renderEggs();
    void displayEggs();
    std::deque<std::shared_ptr<sf::Sprite>> _eggsShapes;

private:
    std::vector<Egg> _eggs;
    static bool startsWith(const std::string& str, const std::string& prefix);
    static std::vector<std::string> splitStr(const std::string &str, char delimiter);
    std::string _eggTexturePath = "../../resources/Egg.png";
    sf::Texture _eggTexture;
};
