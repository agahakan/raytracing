#include "Lambertian.hpp"
#include "../Rtweekend/Rtweekend.hpp"

Lambertian::Lambertian(const color& a)
    : albedo(a) {}

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, ScatterRecord& srec) const {
    Vec3 scatter_direction = rec.normal + random_unit_vector();

    // // Catch degenerate scatter direction
    // if (scatter_direction.near_zero())
    //     scatter_direction = rec.normal;

    srec.scattered = Ray(rec.p, scatter_direction);
    srec.attenuation = albedo;
    return true;
}

