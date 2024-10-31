// src/raymath/Color.hpp

#pragma once

#include <algorithm>
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
    Color &operator=(Color const &col);
    Color operator*(double intensity) const
    {
        return Color(r * intensity, g * intensity, b * intensity);
    }

    Color &clamp(float min = 0.0f, float max = 1.0f)
    {
        r = std::clamp(r, min, max);
        g = std::clamp(g, min, max);
        b = std::clamp(b, min, max);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &_stream, Color const &col);
};
