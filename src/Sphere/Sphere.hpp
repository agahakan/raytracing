#pragma once

#include "../Hittable/Hittable.hpp"
#include "../Interval/Interval.hpp"
#include "../Vec3/Vec3.hpp"

class Sphere : public Hittable
{
  public:
    Sphere(const point3 &center, double radius);

    bool hit(const Ray &r, Interval Ray_t, HitRecord &rec) const override;

  private:
    point3 center;
    double radius;
};
