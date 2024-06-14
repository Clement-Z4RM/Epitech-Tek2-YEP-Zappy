/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Modal.cpp
*/

#include "Modal.hpp"

Modal::Modal()
{
    _position = {0, 0};
    _size = {0, 0};
    _color = {0, 0, 0, 0};
}

Modal::~Modal() = default;

void Modal::display(sf::RenderWindow &window)
{
    _modal.setSize(_size);
    _modal.setPosition(_position.x, _position.y);
    _modal.setFillColor(_color);
    window.draw(_modal);
    for (auto &text : _texts) {
        window.draw(*text);
    }
}

void Modal::close()
{
    _texts.clear();
}

void Modal::addText(const std::shared_ptr<sf::Text> &text)
{
    _texts.push_back(text);
}

void Modal::setTexture(std::string texture)
{
    _texture.loadFromFile(texture);
    _modal.setTexture(&_texture);
}

void Modal::setPosition(float x, float y)
{
    _position = {x, y};
}

void Modal::setSize(float width, float height)
{
    _size = {width, height};
}

void Modal::setColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
    _color = {r, g, b, a};
}

void Modal::setOutline(float thickness, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
    _outlineThickness = thickness;
    _outlineColor = {r, g, b, a};
    _modal.setOutlineThickness(thickness);
    _modal.setOutlineColor(sf::Color(r, g, b, a));
}

void Modal::setShadow(float thickness, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
    _shadowThickness = thickness;
    _shadowColor = {r, g, b, a};
    _modal.setOutlineThickness(thickness);
    _modal.setOutlineColor(sf::Color(r, g, b, a));
}