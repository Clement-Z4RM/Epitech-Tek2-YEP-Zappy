/*
** EPITECH PROJECT, 2024
** zappy_gui
** File description:
** Modal.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <memory>

class Modal {
public:
    Modal();
    ~Modal();

    void display(sf::RenderWindow &window);

    void addText(const std::shared_ptr<sf::Text> &text);

    void setTexture(std::string texture);
    void setPosition(float x, float y);
    void setSize(float width, float height);
    void setColor(sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a);
    void setOutline(float thickness, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a);
    void setShadow(float thickness, sf::Uint8 r, sf::Uint8 g, sf::Uint8 b, sf::Uint8 a);

private:
    sf::RectangleShape _modal;
    sf::Texture _texture;
    sf::Color _color;
    sf::Color _outlineColor;
    sf::Color _shadowColor;
    sf::Vector2f _position;
    sf::Vector2f _size;
    float _outlineThickness{};
    float _shadowThickness{};
    std::vector<std::shared_ptr<sf::Text>> _texts;
};
