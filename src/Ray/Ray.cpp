#include "Ray.hpp"

Ray::Ray() {}

Ray::Ray(const point3 &origin, const Vec3 &direction)
    : orig(origin)
    , dir(direction)
{
}

const point3 &Ray::origin() const
{
    return orig;
}

const Vec3 &Ray::direction() const
{
    return dir;
}

point3 Ray::at(double t) const
{
    return orig + t * dir;
}
