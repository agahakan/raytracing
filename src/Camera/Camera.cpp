#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

#include "Camera.hpp"

#include "../Material/Material.hpp"

Camera::Camera(double aspect_ratio, int image_width, int samples_per_pixel)
    : aspect_ratio(aspect_ratio)
    , image_width(image_width)
    , samples_per_pixel(samples_per_pixel)
    , sky_enabled(true)
    , sky_type(SkyType::GRADIENT)
    , sky_solid_color(color(0.5, 0.7, 1.0))
    ,  // Default solid sky color
    sky_gradient_bottom(color(1.0, 1.0, 1.0))
    ,  // White at the bottom
    sky_gradient_top(color(0.5, 0.7, 1.0))
    ,  // Light blue at the top
    max_depth(50)
{
    initialize();
}

void Camera::initialize()
{
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    center = point3(0, 0, 0);

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

    auto viewport_u = Vec3(viewport_width, 0, 0);
    auto viewport_v = Vec3(0, -viewport_height, 0);

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

void Camera::render(const Hittable &world, std::vector<Uint8> &pixels)
{
    pixels.resize(image_width * image_height * 3);

    std::cout << "Starting render...\n";

    auto start = std::chrono::high_resolution_clock::now();

    const int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(num_threads);

    std::atomic<int> next_scanline(0);

    auto render_scanlines = [&](int thread_id)
    {
        while (true) {
            int j = next_scanline.fetch_add(1);
            if (j >= image_height)
                break;

            for (int i = 0; i < image_width; i++) {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    Ray r = get_Ray(i, j);
                    pixel_color += Ray_color(r, world, 0);
                }
                int index = ((image_height - 1 - j) * image_width + i) * 3;
                write_color(pixels, index, pixel_samples_scale * pixel_color);
            }

            if (thread_id == 0 && j % 10 == 0) {
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            }
        }
    };

    for (int t = 0; t < num_threads; ++t) {
        threads[t] = std::thread(render_scanlines, t);
    }

    for (auto &thread : threads) {
        thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::clog << "\nRender complete in " << duration.count() << " seconds.\n";
}

Ray Camera::get_Ray(int i, int j) const
{
    auto offset = sample_square();
    auto pixel_sample =
        pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

    auto ray_origin = center;
    auto ray_direction = pixel_sample - ray_origin;

    return Ray(ray_origin, ray_direction);
}

Vec3 Camera::sample_square() const
{
    return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

color Camera::Ray_color(const Ray &r, const Hittable &world, int depth) const
{
    if (depth >= max_depth) {
        return color(0, 0, 0);
    }

    HitRecord rec;

    if (world.hit(r, Interval(0.001, infinity), rec)) {
        ScatterRecord srec;
        if (rec.mat_ptr->scatter(r, rec, srec)) {
            return srec.attenuation * Ray_color(srec.scattered, world, depth + 1);
        } else {
            return color(0, 0, 0);
        }
    }
    if (!sky_enabled || sky_type == SkyType::NONE) {
        return color(0, 0, 0);
    } else if (sky_type == SkyType::SOLID_COLOR) {
        return sky_solid_color;
    } else if (sky_type == SkyType::GRADIENT) {
        Vec3 unit_direction = unit_vector(r.direction());
        auto t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * sky_gradient_bottom + t * sky_gradient_top;
    } else {
        return color(0, 0, 0);
    }
}

void Camera::set_sky_enabled(bool enabled)
{
    sky_enabled = enabled;
}

void Camera::set_sky_solid_color(const color &c)
{
    sky_type = SkyType::SOLID_COLOR;
    sky_solid_color = c;
    sky_enabled = true;
}

void Camera::set_sky_gradient(const color &bottom_color, const color &top_color)
{
    sky_type = SkyType::GRADIENT;
    sky_gradient_bottom = bottom_color;
    sky_gradient_top = top_color;
    sky_enabled = true;
}
