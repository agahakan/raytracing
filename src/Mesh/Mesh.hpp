#pragma once

#include <vector>
#include <memory>
#include "../Hittable/Hittable.hpp"
#include "Triangle.hpp"

class Mesh : public Hittable {
public:
    Mesh();
    void add_triangle(std::shared_ptr<Triangle> triangle);
    bool hit(const Ray& r, Interval Ray_t, HitRecord& rec) const override;

private:
    std::vector<std::shared_ptr<Triangle>> triangles;
};

