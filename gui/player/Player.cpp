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
    int x = std::stoi(str);
    s >> str;
    int y = std::stoi(str);
    s >> str;
    _orientation = static_cast<Orientation>(std::stoi(str));
    s >> str;
    _level = std::stoi(str);
    s >> str;
    _team = str;
    _playerSprite = std::make_shared<sf::Sprite>();
    sf::Texture *texture = new sf::Texture();
    if (!texture->loadFromFile("./gui/resources/player.png")) {
        std::cerr << "Error loading player texture" << std::endl;
    }
    _playerSprite->setTexture(*texture);
    _playerSprite->setScale(0.15, 0.15);
    setPosition(x, y);
    initPlayerCircle();
}

void Player::setInventory(std::stringstream &s)
{
    std::string str;
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

void Player::setPosition(int x, int y)
{
    _position._x = x;
    _position._y = y;
    int posX = x * 32 + 32;
    int posY = y * 32 + 32;
    _playerSprite->setPosition(posX, posY);
}

void Player::display(sf::RenderWindow &window)
{
    _playerSprite->setPosition(_position._x * 100, _position._y * 100);
    _playerSprite->setRotation(_orientation * 90);
    window.draw(*_playerSprite);
}

std::string Player::getOrientation()
{
    switch (_orientation) {
    case NORTH:
        return "NORTH";
    case EAST:
        return "EAST";
    case SOUTH:
        return "SOUTH";
    case WEST:
        return "WEST";
    }
    return "azimuth error";
}

std::shared_ptr<sf::Sprite> Player::getPlayerSprite(int width, int height, int mapWidth, int mapHeight)
{
    float squareSize = (width * 0.9 / mapWidth) < (height * 0.9 / mapHeight) ? (width * 0.9 / mapWidth) : (height * 0.9 / mapHeight);
    float scale = squareSize / 208;
    _playerSprite->setScale(scale, scale);
    int posX = _position._x * squareSize + width * 0.5 / 2;
    int posY = _position._y * squareSize + height * 0.1 / 2;
    _playerSprite->setPosition(posX, posY);
    return _playerSprite;
}

sf::Color Player::stringToColor(const std::string &str)
{
    std::hash<std::string> hasher;
    size_t hash = hasher(str);
    sf::Uint8 r = (hash & 0xFF0000) >> 16;
    sf::Uint8 g = (hash & 0x00FF00) >> 8;
    sf::Uint8 b = (hash & 0x0000FF);
    return sf::Color(r, g, b);
}

void Player::initPlayerCircle()
{
    _playerCircle->setRadius(50);
    _playerCircle->setFillColor(sf::Color::Transparent);
    _playerCircle->setOutlineThickness(5);
    _playerCircle->setOutlineColor(stringToColor(_team));
    _playerCircle->setPosition(_position._x * 100, _position._y * 100);
}
