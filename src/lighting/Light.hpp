#pragma once

#include "Vec3.hpp"

enum class LightType
{
    Ambient,
    Point,
    Directional
};

struct Light
{
    LightType type;
    double intensity;
    Vec3 position;

    Light(LightType type_, double intensity_);
    Light(LightType type_, double intensity_, const Vec3 &vec);
};
