/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Text.cpp
*/

#include "Text.hpp"

Text::Text() {
    _position = {0, 0};
    _fontSize = 0;
    _style = 0;
    _outlineThickness = 0;
    _shadowThickness = 0;
    _underline = false;
}

Text::~Text() = default;

void Text::setText(std::string &text)
{
    _text.setString(text);
}

void Text::setPosition(float x, float y)
{
    _position = {x, y};
}

void Text::setFont(std::shared_ptr<sf::Font> &font)
{
    _font = font;
    _text.setFont(*_font);
}

void Text::setFontSize(int size)
{
    _fontSize = size;
    _text.setCharacterSize(size);
}

void Text::setSize(float width, float height)
{
    _text.setScale(width, height);
}

void Text::setColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
    _color = {r, g, b, a};
    _text.setFillColor(_color);
}

void Text::setOutline(float thickness, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
    _outlineColor = {r, g, b, a};
    _outlineThickness = thickness;
    _text.setOutlineThickness(thickness);
    _text.setOutlineColor(_outlineColor);
}

void Text::setShadow(float thickness, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a)
{
    _shadowColor = {r, g, b, a};
    _shadowThickness = thickness;
}

void Text::setUnderline(bool underline)
{
    _underline = underline;
    if (underline)
        _style = sf::Text::Underlined;
    else
        _style = sf::Text::Regular;
    _text.setStyle(_style);
}

void Text::display(sf::RenderWindow &window)
{
    _text.setPosition(_position);
    _text.setFillColor(_color);
    _text.setScale(_shadowThickness, _shadowThickness);
    window.draw(_text);
}
