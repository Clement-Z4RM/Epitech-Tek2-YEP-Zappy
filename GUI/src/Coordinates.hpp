/*
** EPITECH PROJECT, 2024
** Epitech-Tek2-YEP-Zappy
** File description:
** Coordinates.hpp
*/

#pragma once

class Coordinates {
public:
    Coordinates() = default;
    Coordinates(int x, int y);
    ~Coordinates() = default;

    int x;
    int y;

    bool operator==(const Coordinates &rhs) const;
};
