#include <fstream>
#include <iostream>

#include <SDL2/SDL.h>

#include "camera.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "rtweekend.hpp"
#include "sphere.hpp"

double hit_sphere(const point3 &center, double radius, const ray &r)
{
    vec3 oc = center - r.origin();
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

color ray_color(const ray &r, const hittable &world)
{
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
    hittable_list world;

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;

    cam.render(world);
}

//  // Create pixel data for the gradient image
//     std::vector<Uint8> pixels(image_width * image_height * 3);  // RGB format
//     for (int j = 0; j < image_height; j++) {
//         std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
//         for (int i = 0; i < image_width; i++) {
//             auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
//             auto ray_direction = pixel_center - camera_center;
//             ray r(camera_center, ray_direction);

//             color pixel_color = ray_color(r);

//             int pixel_index = (j * image_width + i) * 3;
//             write_color(pixels, pixel_index, pixel_color);
//         }
//     }

//     SDLGraphics graphics;
//     if (!graphics.init("Raytracing C++", image_width, image_height)) {
//         return 1;
//     }

//     bool running = true;
//     while (running) {
//         running = graphics.processEvents();
//         graphics.render(pixels, image_width, image_height);
//     }
//     graphics.cleanup();

//     return 0;