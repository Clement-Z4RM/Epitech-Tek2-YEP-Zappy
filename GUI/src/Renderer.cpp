/*
** EPITECH PROJECT, 2024
** Epitech-Tek2-YEP-Zappy
** File description:
** Renderer.cpp
*/

#include "Renderer.hpp"

namespace gui {

        Renderer::Renderer(int nodes) : _nodes(nodes)
        {
            _window.create(sf::VideoMode(1920, 1080), "Trantor", sf::Style::Default | sf::Style::Close);
            for (int i = 0; i < _nodes; i++) {
                for (int j = 0; j < _nodes; j++) {
                    std::shared_ptr<Node> node = std::make_shared<Node>(i, j);
                    _nodeList.push_back(node);
                }
            }
            initVertices();
            Bresenham(_vertices.at(0), _vertices.at(1));
            Bresenham(_vertices.at(1), _vertices.at(2));
            Bresenham(_vertices.at(2), _vertices.at(0));
        }

        Renderer::~Renderer()
        {
            _window.close();
        }

        void Renderer::initVertices()
        {
            Coordinates coord1(8, 10);
            Color color1(255, 0, 0, 255);
            std::shared_ptr<Vertices> vertice1 = std::make_shared<Vertices>();
            vertice1->setCoordinates(coord1);
            vertice1->setColor(color1);
            _vertices.push_back(vertice1);
            Coordinates coord2(1, 3);
            Color color2(0, 255, 0, 255);
            std::shared_ptr<Vertices> vertice2 = std::make_shared<Vertices>();
            vertice2->setCoordinates(coord2);
            vertice2->setColor(color2);
            _vertices.push_back(vertice2);
            Coordinates coord3(9, 1);
            Color color3(0, 102, 205, 255);
            std::shared_ptr<Vertices> vertice3 = std::make_shared<Vertices>();
            vertice3->setCoordinates(coord3);
            vertice3->setColor(color3);
            _vertices.push_back(vertice3);
        }

        void Renderer::Bresenham(std::shared_ptr<Vertices> v1, std::shared_ptr<Vertices> v2)
        {
            int x0 = v1->getCoordinates().x;
            int y0 = v1->getCoordinates().y;
            int x1 = v2->getCoordinates().x;
            int y1 = v2->getCoordinates().y;
            int dx = abs(x1 - x0);
            int dy = abs(y1 - y0);
            int sx = (x0 < x1) ? 1 : -1;
            int sy = (y0 < y1) ? 1 : -1;
            int err = dx - dy;
            std::vector<std::shared_ptr<Vertices>> verticeList;

            while (true) {
                if (x0 == x1 && y0 == y1)
                    break;
                int e2 = 2 * err;
                if (e2 > -dy) {
                    err -= dy;
                    x0 += sx;
                }
                if (e2 < dx) {
                    err += dx;
                    y0 += sy;
                }
                Coordinates coo(x0, y0);
                std::shared_ptr<Vertices> new_vertice = std::make_shared<Vertices>();
                new_vertice->setCoordinates(coo);
                verticeList.push_back(new_vertice);
            }

            int len = verticeList.size();
            int index = 0;
            for (auto &vertice : verticeList) {
                Color a = v1->getColor();
                Color b = v2->getColor();
                int r = a.r + (b.r - a.r) * index / len;
                int g = a.g + (b.g - a.g) * index / len;
                int bl = a.b + (b.b - a.b) * index / len;
                Color color(r, g, bl, 255);
                vertice->setColor(color);
                _vertices.push_back(vertice);
                index++;
            }
            return;
        }

        void Renderer::drawWindow()
        {
            for (auto &node : _nodeList) {
                for (auto &vertice : _vertices) {
                    if (node->getCoordinates() == vertice->getCoordinates()) {
                        node->getRect()->setFillColor(vertice->getColor().getSFMColor());
                        break;
                    } else {
                        node->getRect()->setFillColor({255, 255, 255, 255});
                    }
                }
                _window.draw(*node->getRect());
            }
            _window.display();
        }

        bool Renderer::isOpen()
        {
            return _window.isOpen();
        }

        void Renderer::clearWindow()
        {
            _window.clear();
        }

        void Renderer::handleEvent()
        {
            int select = 0;
            sf::Event event;
            if (_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    _window.close();
                }
                if (event.key.code == sf::Keyboard::Escape && event.type == sf::Event::KeyReleased) {
                    _window.close();
                    return;
                }
            }
        }

} // gui