#include <fstream>
#include <iostream>
#include <memory>
#include <thread>

#include "./Backend/SDLGraphics.hpp"
#include "./Camera/Camera.hpp"
#include "./Hittable/Hittable.hpp"
#include "./HittableList/HittableList.hpp"
#include "./Mesh/Mesh.hpp"
#include "./Mesh/SphereMeshGenerator.hpp"
#include "./Mesh/Triangle.hpp"
#include "./Rtweekend/Rtweekend.hpp"

int main()
{
    HittableList world;

    Mesh sphere_mesh;
    generate_sphere_mesh(sphere_mesh, point3(0, 0, -1), 0.5, 4, 4);
    world.add(std::make_shared<Mesh>(sphere_mesh));

    Camera cam(16.0 / 9.0, 400, 50);

    SDLGraphics graphics;
    if (!graphics.init("Raytracing C++", cam.image_width, cam.image_height)) {
        return 1;
    }

    std::vector<Uint8> pixels(cam.image_width * cam.image_height * 3);
    std::thread render_thread([&]() { cam.render(world, pixels); });

    bool running = true;
    while (running) {
        running = graphics.processEvents();
        graphics.render(pixels, cam.image_width, cam.image_height);
    }
    graphics.cleanup();

    return 0;
}
