// src/raymath/Color.cpp

#include <cmath>
#include <iostream>

#include "Color.hpp"

Color::Color()
    : r(0)
    , b(0)
    , g(0)
{
}

Color::Color(float iR, float iG, float iB)
    : r(iR)
    , g(iG)
    , b(iB)
{
}

Color::~Color() {}

/**
 * Implementation of the + operator :
 * Adding two colors is done by just adding the different components together :
 * (r1, g1, b1) + (r2, g2, b2) = (r1 + r2, g1 + g2, b1 + b2)
 */
Color Color::operator+(Color const &col)
{
    Color c;
    c.r = fmax(fmin(r + col.r, 1), 0);
    c.g = fmax(fmin(g + col.g, 1), 0);
    c.b = fmax(fmin(b + col.b, 1), 0);
    return c;
}

/**
 * Implementation of the * operator :
 * Multiplying a color by a scalar is done by multiplying each component by the scalar :
 * (r, g, b) * s = (r * s, g * s, b * s)
 */
Color Color::operator*(float scalar) const
{
    return Color(std::max(std::min(r * scalar, 1.0f), 0.0f),
                 std::max(std::min(g * scalar, 1.0f), 0.0f),
                 std::max(std::min(b * scalar, 1.0f), 0.0f));
}

/**
 * Implementation of the * operator :
 * Multiplying a color by another color is done by multiplying each component by the corresponding component :
 * (r1, g1, b1) * (r2, g2, b2) = (r1 * r2, g1 * g2, b1 * b2)
 */
Color Color::operator*(Color const &col) const
{
    return Color(std::max(std::min(r * col.r, 1.0f), 0.0f),
                 std::max(std::min(g * col.g, 1.0f), 0.0f),
                 std::max(std::min(b * col.b, 1.0f), 0.0f));
}

/**
 * Overriding the assignment operator
 */
Color &Color::operator=(Color const &col)
{
    r = col.r;
    g = col.g;
    b = col.b;
    return *this;
}

/**
 * Here we implement the << operator :
 * We take each component and append it to he stream, giving it a nice form on the console
 */
std::ostream &operator<<(std::ostream &_stream, Color const &col)
{
    return _stream << "(" << col.r << "," << col.g << "," << col.b << ")";
}
