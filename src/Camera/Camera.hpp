#pragma once

#include <vector>

#include "../Color/Color.hpp"
#include "../Hittable/Hittable.hpp"
#include "../Ray/Ray.hpp"

class Camera
{
  public:
    Camera(double aspect_ratio = 1.0, int image_width = 100, int samples_per_pixel = 10);

    int image_width;
    int image_height;

    void render(const Hittable &world, std::vector<Uint8> &pixels);

    void set_sky_enabled(bool enabled);
    void set_sky_solid_color(const color &c);
    void set_sky_gradient(const color &bottom_color, const color &top_color);

  private:
    double aspect_ratio;
    int samples_per_pixel;
    double pixel_samples_scale;

    bool sky_enabled;
    enum class SkyType
    {
        NONE,
        SOLID_COLOR,
        GRADIENT
    } sky_type;
    color sky_solid_color;
    color sky_gradient_bottom;
    color sky_gradient_top;

    int max_depth;

    point3 center;
    point3 pixel00_loc;
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;

    void initialize();
    Ray get_Ray(int i, int j) const;
    Vec3 sample_square() const;
    color Ray_color(const Ray &r, const Hittable &world, int depth) const;
};
