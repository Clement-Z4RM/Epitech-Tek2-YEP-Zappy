/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Text.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <memory>

class Text {
public:
    Text();
    ~Text();

    void setText(std::string &text);
    void setPosition(float x, float y);
    void setFont(std::shared_ptr<sf::Font> &font);
    void setFontSize(int size);
    void setSize(float width, float height);
    void setColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a);
    void setOutline(float thickness, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a);
    void setShadow(float thickness, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a);
    void setUnderline(bool underline);

    void display(sf::RenderWindow &window);

private:
    sf::Text _text;
    std::shared_ptr<sf::Font> _font;
    sf::Color _color;
    sf::Color _outlineColor;
    sf::Color _shadowColor;
    sf::Vector2f _position;
    int _fontSize;
    int _style;
    int _outlineThickness;
    int _shadowThickness;
    bool _underline;
};