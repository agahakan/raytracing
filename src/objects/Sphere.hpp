#pragma once

#include "Object.hpp"
#include "Utility.hpp"

struct Sphere : public Object
{
    Vec3 center;
    double radius;

    Sphere(const Vec3 &c, double r, const Color &col, double reflection_ = 0.0);

    double Intersect(const Ray &ray, double t_min, double t_max) const override;
    Vec3 getNormal(const Vec3 &P) const override;
};


