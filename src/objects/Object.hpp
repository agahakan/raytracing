#pragma once

#include "Vec3.hpp"
#include "Image.hpp"
#include "Ray.hpp"

struct Object
{
    Color color;
    double reflection;

    Object(const Color &col, double reflection_ = 0.0);

    virtual double Intersect(const Ray &ray, double t_min, double t_max) const = 0;
    virtual Vec3 getNormal(const Vec3 &P) const = 0;
    virtual ~Object() = default;
};
