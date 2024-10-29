#include "Triangle.hpp"

Triangle::Triangle(const point3 &v0,
                   const point3 &v1,
                   const point3 &v2,
                   std::shared_ptr<Material> mat_ptr)
    : v0(v0)
    , v1(v1)
    , v2(v2)
    , mat_ptr(mat_ptr)
{
    normal = unit_vector(cross(v1 - v0, v2 - v0));
}

bool Triangle::hit(const Ray &r, Interval Ray_t, HitRecord &rec) const
{
    const double EPSILON = 1e-8;
    Vec3 edge1 = v1 - v0;
    Vec3 edge2 = v2 - v0;
    Vec3 h = cross(r.direction(), edge2);
    double a = dot(edge1, h);

    if (fabs(a) < EPSILON)
        return false;

    double f = 1.0 / a;
    Vec3 s = r.origin() - v0;
    double u = f * dot(s, h);

    if (u < 0.0 || u > 1.0)
        return false;

    Vec3 q = cross(s, edge1);
    double v = f * dot(r.direction(), q);

    if (v < 0.0 || u + v > 1.0)
        return false;

    double t = f * dot(edge2, q);

    if (Ray_t.surrounds(t)) {
        rec.t = t;
        rec.p = r.at(t);
        rec.set_face_normal(r, normal);
        rec.mat_ptr = mat_ptr;
        return true;
    }

    return false;
}
