#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <thread>
#include <vector>

#include "Config.hpp"
#include "Image.hpp"
#include "Light.hpp"
#include "Plane.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Trace.hpp"
#include "Vec3.hpp"

int main()
{
    Config config;
    try {
        config = config.loadConfig("../config.json");
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }

    const int canvas_width = config.canvas_width;
    const int canvas_height = config.canvas_height;
    const std::string filename = config.filename;

    Image image(canvas_width, canvas_height);
    Scene scene;

    int grid_size = config.grid_size;
    double spacing = config.spacing;
    double amplitude = config.amplitude;
    double frequency = config.frequency;
    double min_y_offset = config.min_y_offset;
    double min_z = config.min_z;

    double base_z = min_z + grid_size * spacing;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = -grid_size; i <= grid_size; ++i) {
        for (int j = -grid_size; j <= grid_size; ++j) {
            double x = i * spacing;
            double z = j * spacing + base_z;
            double wave_value = sin(frequency * (x + z));
            double y = amplitude * wave_value + min_y_offset;
            double r = dis(gen);
            double g = dis(gen);
            double b = dis(gen);
            Color color(r, g, b);
            double reflection = 0.2;
            auto sphere = std::make_shared<Sphere>(Vec3(x, y, z), 1.0, color, reflection);
            scene.AddObject(sphere);
        }
    }

    std::shared_ptr<Object> groundPlane =
        std::make_shared<Plane>(Vec3(0, -1, 0), Vec3(0, 1, 0), Color(1, 1, 1), 0.5);
    scene.AddObject(groundPlane);

    scene.AddLight(Light(LightType::Ambient, 0.2));
    scene.AddLight(Light(LightType::Point, 2.8, Vec3(2, 1, 0)));
    scene.AddLight(Light(LightType::Directional, 0.2, Vec3(1, 4, 4)));

    auto start_time = std::chrono::high_resolution_clock::now();

    RenderScene(scene, image, canvas_width, canvas_height);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;

    const char *output_filename = filename.c_str();
    image.WriteFile(output_filename);
    std::cout << "Image saved as " << output_filename << std::endl;
    std::cout << "Rendering time: " << elapsed_time.count() << " seconds" << std::endl;

    return 0;
}
