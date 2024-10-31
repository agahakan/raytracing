#include <chrono>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <thread>
#include <vector>

#include "Light.hpp"
#include "Vec3.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "Trace.hpp"
#include "Scene.hpp"
#include "Image.hpp"

int main()
{
    const int canvas_width = 1920;
    const int canvas_height = 1080;
    Image image(canvas_width, canvas_height);
    Scene scene;

    const int grid_size = 6;
    const double spacing = 2.5;
    const double amplitude = 1.0;
    const double frequency = 0.5;

    const double min_y_offset = 1.0;
    const double min_z = 6.0;
    const double base_z = min_z + grid_size * spacing;

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

    const Vec3 O(0, 0, 0);

    auto start_time = std::chrono::high_resolution_clock::now();

    auto num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0)
        num_threads = 4;
    std::vector<std::thread> threads;
    int rows_per_thread = canvas_height / num_threads;

    RenderScene(scene, image, canvas_width, canvas_height);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;

    const char *filename = "raytraced_wave_field.png";
    image.WriteFile(filename);
    std::cout << "Image saved as " << filename << std::endl;
    std::cout << "Rendering time: " << elapsed_time.count() << " seconds" << std::endl;

    return 0;
}
