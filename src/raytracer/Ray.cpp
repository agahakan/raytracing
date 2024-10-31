#include "Ray.hpp"

Ray::Ray(const Vec3 &origin_, const Vec3 &direction_)
    : origin(origin_), direction(direction_.normalize()) {}

