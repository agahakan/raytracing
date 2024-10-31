#include "Light.hpp"

Light::Light(LightType type_, double intensity_)
    : type(type_), intensity(intensity_), position(0, 0, 0) {}

Light::Light(LightType type_, double intensity_, const Vec3 &vec)
    : type(type_), intensity(intensity_), position(vec) {}

