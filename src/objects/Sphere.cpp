#include "Sphere.hpp"

Sphere::Sphere(const Vec3 &c, double r, const Color &col, double reflection_)
    : Object(col, reflection_), center(c), radius(r) {}

double Sphere::Intersect(const Ray &ray, double t_min, double t_max) const
{
    Vec3 CO = ray.origin - center;
    double a = dot(ray.direction, ray.direction);
    double b = 2.0 * dot(CO, ray.direction);
    double c = dot(CO, CO) - radius * radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return INF;
    }

    double sqrt_discriminant = std::sqrt(discriminant);
    double t1 = (-b + sqrt_discriminant) / (2.0 * a);
    double t2 = (-b - sqrt_discriminant) / (2.0 * a);

    if (t1 >= t_min && t1 <= t_max) {
        return t1;
    }

    if (t2 >= t_min && t2 <= t_max) {
        return t2;
    }

    return INF;
}

Vec3 Sphere::getNormal(const Vec3 &P) const
{
    return (P - center).normalize();
}

