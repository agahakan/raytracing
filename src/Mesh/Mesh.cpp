#include "Mesh.hpp"

Mesh::Mesh() {}

void Mesh::add_triangle(std::shared_ptr<Triangle> triangle) {
    triangles.push_back(triangle);
}

bool Mesh::hit(const Ray& r, Interval Ray_t, HitRecord& rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = Ray_t.max;

    for (const auto& triangle : triangles) {
        if (triangle->hit(r, Interval(Ray_t.min, closest_so_far), temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

