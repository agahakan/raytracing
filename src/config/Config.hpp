#pragma once

#include <fstream>

#include "../math/Vec3.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class Config
{
  public:
    int canvas_width = 1920;
    int canvas_height = 1080;
    std::string filename = "raytraced_wave_field.png";
    int grid_size = 6;
    double spacing = 2.5;
    double amplitude = 1.0;
    double frequency = 0.5;
    double min_y_offset = 1.0;
    double min_z = 6.0;
    Vec3 camera_origin = Vec3(0, 0, 0);

    Config loadConfig(const std::string &filename);
};