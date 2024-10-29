#pragma once

#include "../Hittable/Hittable.hpp"

class Triangle : public Hittable {
public:
    Triangle(const point3& v0, const point3& v1, const point3& v2);

    bool hit(const Ray& r, Interval Ray_t, HitRecord& rec) const override;

private:
    point3 v0, v1, v2;
    Vec3 normal;
};

