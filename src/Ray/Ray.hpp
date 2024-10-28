#pragma once

#include "../Vec3/Vec3.hpp"

class Ray
{
  public:
    Ray();
    Ray(const point3 &origin, const Vec3 &direction);

    const point3 &origin() const;
    const Vec3 &direction() const;
    point3 at(double t) const;

  private:
    point3 orig;  // Doit être défini dans Vec3.hpp
    Vec3 dir;  // Doit être défini dans Vec3.hpp
};
