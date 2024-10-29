#include <fstream>
#include <iostream>
#include <memory>

#include "./Backend/SDLGraphics.hpp"
#include "./Camera/Camera.hpp"
#include "./Hittable/Hittable.hpp"
#include "./HittableList/HittableList.hpp"
#include "./Rtweekend/Rtweekend.hpp"
#include "./Sphere/Sphere.hpp"

double hit_Sphere(const point3 &center, double radius, const Ray &r)
{
    Vec3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = h * h - a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - std::sqrt(discriminant)) / a;
    }
}

color Ray_color(const Ray &r, const Hittable &world)
{
    HitRecord rec;
    if (world.hit(r, Interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    Vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
    HittableList world;

    world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100));

    Camera cam(16.0 / 9.0, 400, 100);

    SDLGraphics graphics;
    if (!graphics.init("Raytracing C++", cam.image_width, cam.image_height)) {
        return 1;
    }

    std::vector<Uint8> pixels;
    cam.render(world, pixels);

    bool running = true;
    while (running) {
        running = graphics.processEvents();
        graphics.render(pixels, cam.image_width, cam.image_height);
    }
    graphics.cleanup();

    return 0;
}
