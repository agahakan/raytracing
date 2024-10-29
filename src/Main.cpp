#include <fstream>
#include <iostream>
#include <memory>
#include <thread>

#include "./Backend/SDLGraphics.hpp"
#include "./Camera/Camera.hpp"
#include "./Hittable/Hittable.hpp"
#include "./HittableList/HittableList.hpp"
#include "./Rtweekend/Rtweekend.hpp"
#include "./Mesh/Mesh.hpp"
#include "./Mesh/Triangle.hpp"
#include "./Mesh/SphereMeshGenerator.hpp"

int main() {
    HittableList world;

    // Create a mesh sphere and add it to the world
    auto sphere_mesh = std::make_shared<Mesh>();
    generate_sphere_mesh(*sphere_mesh, point3(0, 0, -1), 0.5, 10, 10);
    world.add(sphere_mesh);

    Camera cam(16.0 / 9.0, 400, 100);

    // cam.set_sky_enabled(false);
    // cam.set_sky_solid_color(color(0.8, 0.8, 0.8));
    cam.set_sky_gradient(color(1.0, 0.0, 0.0), color(0.0, 0.0, 1.0));

    SDLGraphics graphics;
    if (!graphics.init("Raytracing C++", cam.image_width, cam.image_height)) {
        return 1;
    }

    std::vector<Uint8> pixels(cam.image_width * cam.image_height * 3, 0);

    std::thread render_thread([&]() {
        cam.render(world, pixels);
    });

    bool running = true;
    while (running) {
        running = graphics.processEvents();
        graphics.render(pixels, cam.image_width, cam.image_height);
    }

    render_thread.join();
    graphics.cleanup();

    return 0;
}
