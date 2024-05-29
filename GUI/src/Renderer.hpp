/*
** EPITECH PROJECT, 2024
** Epitech-Tek2-YEP-Zappy
** File description:
** Renderer.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include <memory>
#include <iostream>
#include "Rasterization.hpp"

namespace gui {

    class Node {
    public:
        Node(int x, int y) {
            auto rect = std::make_shared<sf::RectangleShape>();
            rect->setSize(sf::Vector2f(50, 50));
            rect->setPosition(x * 50, y * 50);
            rect->setFillColor(sf::Color::White);
            rect->setOutlineThickness(3);
            rect->setOutlineColor({0, 0, 0, 200});
            _rect = rect;
            Coordinates coord(x, y);
            Color color(255, 255, 255, 255);
            setCoordinates(coord);
            setColor(color);
        };
        ~Node() = default;

        void setCoordinates(Coordinates &coordinates) { _coordinates = coordinates; }
        void setColor(Color &color) { _color = color; }
        Coordinates getCoordinates() { return _coordinates; }
        Color getColor() { return _color; }
        std::shared_ptr<sf::RectangleShape> getRect() { return _rect; }

    private:
        Coordinates _coordinates {};
        Color _color {};
        std::shared_ptr<sf::RectangleShape> _rect;
    };

    class Renderer {
    public:
        Renderer(int nodes);
        ~Renderer();

        void drawWindow();
        bool isOpen();
        void clearWindow();
        void handleEvent();

        sf::RenderWindow &getWindow() { return _window; }

        void initVertices();

        void Bresenham(std::shared_ptr<Vertices> v1, std::shared_ptr<Vertices> v2);

        std::deque<std::shared_ptr<Vertices>> &getVertices() { return _vertices; }

    private:
        sf::RenderWindow _window;
        int _nodes;
        std::deque<std::shared_ptr<Node>> _nodeList;
        std::deque<std::shared_ptr<Vertices>> _vertices;
    };

} // gui
