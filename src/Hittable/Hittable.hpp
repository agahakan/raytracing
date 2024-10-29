#pragma once

#include <memory>

#include "../Interval/Interval.hpp"
#include "../Ray/Ray.hpp"

class Material;

struct HitRecord
{
    point3 p;
    Vec3 normal;
    double t;
    bool front_face;
    std::shared_ptr<Material> mat_ptr;

    void set_face_normal(const Ray &r, const Vec3 &outward_normal);
};

class Hittable
{
  public:
    virtual bool hit(const Ray &r,
                     Interval Ray_t,
                     HitRecord &rec) const = 0;  // Méthode virtuelle pure
};
