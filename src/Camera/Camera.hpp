#pragma once

#include <fstream>
#include <iostream>
#include <limits>

#include "../Backend/SDLGraphics.hpp"
#include "../Color/Color.hpp"
#include "../Hittable/Hittable.hpp"
#include "../Ray/Ray.hpp"
#include "../Rtweekend/Rtweekend.hpp"

class Camera
{
  public:
    Camera(double aspect_ratio = 1.0, int image_width = 100, int samples_per_pixel = 10);

    void render(const Hittable &world, std::vector<Uint8> &pixels);

    double aspect_ratio;
    int image_width;
    int image_height;
    int samples_per_pixel;

  private:
    void initialize();

    double pixel_samples_scale;
    point3 center;
    point3 pixel00_loc;
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;

    Ray get_Ray(int i, int j) const;
    Vec3 sample_square() const;
    color Ray_color(const Ray &r, const Hittable &world) const;
};
