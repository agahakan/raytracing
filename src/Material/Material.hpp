#pragma once

#include "../Color/Color.hpp"
#include "../Hittable/Hittable.hpp"
#include "../Ray/Ray.hpp"

struct ScatterRecord
{
    Ray scattered;
    color attenuation;
};

class Material
{
  public:
    virtual bool scatter(const Ray &r_in, const HitRecord &rec, ScatterRecord &srec) const = 0;
};
