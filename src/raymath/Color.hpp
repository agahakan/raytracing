// src/raymath/Color.hpp

#pragma once

#include <iostream>

class Color
{
  public:
    Color();
    Color(float r, float g, float b);
    ~Color();

    float r = 0;
    float b = 0;
    float g = 0;

    Color operator+(Color const &col);
    Color operator*(float scalar) const;  // Multiplier par un scalaire
    Color operator*(Color const &col) const;  // Multiplier par une autre couleur
    Color Clamp() const;  // Clamp les valeurs de couleur entre 0 et 1
    Color &operator=(Color const &col);
    friend std::ostream &operator<<(std::ostream &_stream, Color const &col);
};
