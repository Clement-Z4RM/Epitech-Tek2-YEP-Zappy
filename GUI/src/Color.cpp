//
// Created by mzucchero on 5/22/24.
//

#include "Color.hpp"

Color::Color(int r, int g, int b, int a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

sf::Color Color::getSFMColor()
{
    return sf::Color(r, g, b, a);
}
