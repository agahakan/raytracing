#pragma once

#include "../Hittable/Hittable.hpp"
#include "../Material/Material.hpp"
#include <memory>

class Triangle : public Hittable {
public:
    Triangle(const point3& v0, const point3& v1, const point3& v2, std::shared_ptr<Material> mat_ptr);

    bool hit(const Ray& r, Interval Ray_t, HitRecord& rec) const override;

private:
    point3 v0, v1, v2;
    Vec3 normal;
    std::shared_ptr<Material> mat_ptr;
};

