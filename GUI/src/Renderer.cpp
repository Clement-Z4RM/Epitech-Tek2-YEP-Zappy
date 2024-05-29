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
            Bresenham();
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

        void Renderer::Bresenham()
        {
            return;
        }

        void Renderer::drawWindow()
        {
            for (auto &node : _nodeList) {
                for (auto &vertice : _vertices) {
                    if (node->getCoordinates() == vertice->getCoordinates()) {
                        node->getRect()->setFillColor(vertice->getColor().getSFMColor());
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
} // gui