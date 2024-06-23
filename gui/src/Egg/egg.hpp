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
    std::deque<std::shared_ptr<sf::Sprite>> _eggsShapes;

private:
    std::vector<std::shared_ptr<Egg>> _eggs;
    static bool startsWith(const std::string& str, const std::string& prefix);
    static std::vector<std::string> splitStr(const std::string &str, char delimiter);
    std::string _eggTexturePath = "./gui/resources/Egg.png";
    sf::Texture _eggTexture;
    int _nbEggsCreated = 0;
};
