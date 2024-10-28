#include "Hittable.hpp"

void HitRecord::set_face_normal(const Ray &r, const Vec3 &outward_normal)
{
    // Définit le vecteur normal du record de frappe.
    // REMARQUE : le paramètre `outward_normal` est supposé avoir une longueur unitaire.

    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
}
