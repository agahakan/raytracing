#include "Config.hpp"

Config Config::loadConfig(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open configuration file: " + filename);
    }

    json j;
    file >> j;

    Config config;
    config.canvas_width = j["canvas_width"];
    config.canvas_height = j["canvas_height"];
    config.filename = j["filename"];
    config.grid_size = j["grid"]["grid_size"];
    config.spacing = j["grid"]["spacing"];
    config.amplitude = j["grid"]["amplitude"];
    config.frequency = j["grid"]["frequency"];
    config.min_y_offset = j["grid"]["min_y_offset"];
    config.min_z = j["grid"]["min_z"];
    config.camera_origin =
        Vec3(j["camera"]["origin"][0], j["camera"]["origin"][1], j["camera"]["origin"][2]);

    return config;
}