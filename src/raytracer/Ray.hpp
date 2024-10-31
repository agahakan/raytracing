#pragma once

#include "../math/Vec3.hpp"

struct Ray
{
    Vec3 origin;
    Vec3 direction;

    Ray(const Vec3 &origin_, const Vec3 &direction_);
};
