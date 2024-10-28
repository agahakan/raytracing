#pragma once

#include <iostream>

#include "vec3.hpp"

using color = vec3;

void write_color(std::ostream &out, const color &pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

void write_color(std::vector<Uint8> &pixels, int index, const color &pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    pixels[index] = static_cast<Uint8>(255.999 * pixel_color.x());
    pixels[index + 1] = static_cast<Uint8>(255.999 * pixel_color.y());
    pixels[index + 2] = static_cast<Uint8>(255.999 * pixel_color.z());
}