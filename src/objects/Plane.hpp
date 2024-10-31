#pragma once

#include "Utility.hpp"
#include "Object.hpp"

struct Plane : public Object
{
    Vec3 c;
    Vec3 n;

    Plane(const Vec3 &c_, const Vec3 &n_, const Color &col, double reflection_ = 0.0);

    double Intersect(const Ray &ray, double t_min, double t_max) const override;
    Vec3 getNormal(const Vec3 &P) const override;
};
