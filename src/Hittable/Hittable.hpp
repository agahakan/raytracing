#pragma once

#include "../Interval/Interval.hpp"
#include "../Ray/Ray.hpp"

class HitRecord
{
  public:
    point3 p;  // Point d'impact
    Vec3 normal;  // Normale à la surface au point d'impact
    double t;  // Distance du Rayon à l'impact
    bool front_face;  // Indique si la normale est tournée vers l'extérieur

    void set_face_normal(const Ray &r, const Vec3 &outward_normal);
};

class Hittable
{
  public:
    virtual bool hit(const Ray &r,
                     Interval Ray_t,
                     HitRecord &rec) const = 0;  // Méthode virtuelle pure
};
