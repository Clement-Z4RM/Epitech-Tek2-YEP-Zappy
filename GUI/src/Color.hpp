/*
** EPITECH PROJECT, 2024
** Epitech-Tek2-YEP-Zappy
** File description:
** Color.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>

class Color {
public:
    Color() = default;
    Color(int r, int g, int b, int a);
    ~Color() = default;

    sf::Color getSFMColor();

    int r;
    int g;
    int b;
    int a;
};
