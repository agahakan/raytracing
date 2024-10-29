#pragma once

#include "Material.hpp"

class Lambertian : public Material
{
  public:
    Lambertian(const color &albedo);

    virtual bool scatter(const Ray &r_in, const HitRecord &rec, ScatterRecord &srec) const override;

  private:
    color albedo;
};
