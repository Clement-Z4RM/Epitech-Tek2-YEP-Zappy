/*
** EPITECH PROJECT, 2024
** Epitech-Tek2-YEP-Zappy
** File description:
** Rasterization.hpp
*/

#pragma once
#include "Vector/Vector.hpp"
#include "Color.hpp"
#include "Coordinates.hpp"

class Vertices {
public:
    Vertices() = default;
    ~Vertices() = default;

    void setCoordinates(Coordinates &coordinates) { _coordinates = coordinates; }
    void setColor(Color &color) { _color = color; }
    Coordinates getCoordinates() { return _coordinates; }
    Color getColor() { return _color; }

private:
    Coordinates _coordinates {};
    Color _color {};
};

class Rasterization {
public:
    Rasterization();
    ~Rasterization();

private:
};
