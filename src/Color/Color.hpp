#pragma once

#include <iostream>

#include <SDL2/SDL.h>

#include "../Vec3/Vec3.hpp"

using color = Vec3;

void write_color(std::ostream &out, const color &pixel_color);
void write_color(std::vector<Uint8> &pixels, int index, const color &pixel_color);