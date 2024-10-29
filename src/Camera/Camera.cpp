#include "Camera.hpp"

void Camera::render(const Hittable &world, SDLGraphics &graphics)
{
    initialize();

    std::vector<Uint8> pixels(image_width * image_height * 3);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            color pixel_color(0, 0, 0);
            for (int sample = 0; sample < samples_per_pixel; sample++) {
                Ray r = get_Ray(i, j);
                pixel_color += Ray_color(r, world);
            }
            int index = (j * image_width + i) * 3;
            write_color(pixels, index, pixel_samples_scale * pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";

    graphics.render(pixels, image_width, image_height);
}

int Camera::get_image_height() const
{
    return image_height;
}

void Camera::initialize()
{
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    center = point3(0, 0, 0);

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);

    auto viewport_u = Vec3(viewport_width, 0, 0);
    auto viewport_v = Vec3(0, -viewport_height, 0);

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

Ray Camera::get_Ray(int i, int j) const
{
    // Construct a Camera Ray originating from the origin and directed at randomly sampled
    // point around the pixel location i, j.

    auto offset = sample_square();
    auto pixel_sample =
        pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

    auto Ray_origin = center;
    auto Ray_direction = pixel_sample - Ray_origin;

    return Ray(Ray_origin, Ray_direction);
}

Vec3 Camera::sample_square() const
{
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

color Camera::Ray_color(const Ray &r, const Hittable &world) const
{
    HitRecord rec;

    if (world.hit(r, Interval(0, infinity), rec)) {
        Vec3 direction = random_on_hemiSphere(rec.normal);
        return 0.5 * Ray_color(Ray(rec.p, direction), world);
    }

    Vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}
