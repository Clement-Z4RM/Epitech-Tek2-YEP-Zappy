/*
** EPITECH PROJECT, 2024
** Epitech-Tek2-YEP-Zappy
** File description:
** Coordinates.cpp
*/

#include "Coordinates.hpp"

Coordinates::Coordinates(int x, int y)
{
    this->x = x;
    this->y = y;
}

bool Coordinates::operator==(const Coordinates &rhs) const
{
    return x == rhs.x &&
           y == rhs.y;
}
