#include "Plane.hpp"

Plane::Plane(const Vec3 &c_, const Vec3 &n_, const Color &col, double reflection_)
    : Object(col, reflection_), c(c_), n(n_.normalize()) {}

double Plane::Intersect(const Ray &ray, double t_min, double t_max) const
{
    double denom = dot(ray.direction, n);

    if (std::abs(denom) < 1e-6) {
        return INF;
    }

    double num = dot(c - ray.origin, n);
    double t = num / denom;

    if (t >= t_min && t <= t_max) {
        return t;
    }

    return INF;
}

Vec3 Plane::getNormal(const Vec3 &P) const
{
    return n;
}

