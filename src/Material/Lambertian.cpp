#include "Lambertian.hpp"

#include "../Utils/Utils.hpp"

Lambertian::Lambertian(const color &a)
    : albedo(a)
{
}

bool Lambertian::scatter(const Ray &r_in, const HitRecord &rec, ScatterRecord &srec) const
{
    Vec3 scatter_direction = rec.normal + random_unit_vector();

    srec.scattered = Ray(rec.p, scatter_direction);
    srec.attenuation = albedo;
    return true;
}
