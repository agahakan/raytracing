#include <cmath>

#include "SphereMeshGenerator.hpp"

#include "../Material/Lambertian.hpp"

void generate_sphere_mesh(Mesh &mesh,
                          const point3 &center,
                          double radius,
                          int longitude_segments,
                          int latitude_segments,
                          std::shared_ptr<Material> mat_ptr)
{
    std::vector<point3> vertices;

    for (int y = 0; y <= latitude_segments; ++y) {
        double theta = y * pi / latitude_segments;
        double sin_theta = sin(theta);
        double cos_theta = cos(theta);

        for (int x = 0; x <= longitude_segments; ++x) {
            double phi = x * 2 * pi / longitude_segments;
            double sin_phi = sin(phi);
            double cos_phi = cos(phi);

            double vx = radius * sin_theta * cos_phi;
            double vy = radius * cos_theta;
            double vz = radius * sin_theta * sin_phi;

            vertices.push_back(center + Vec3(vx, vy, vz));
        }
    }

    // Create triangles
    for (int y = 0; y < latitude_segments; ++y) {
        for (int x = 0; x < longitude_segments; ++x) {
            int first = y * (longitude_segments + 1) + x;
            int second = first + longitude_segments + 1;

            point3 v0 = vertices[first];
            point3 v1 = vertices[second];
            point3 v2 = vertices[first + 1];
            point3 v3 = vertices[second + 1];

            // First triangle
            mesh.add_triangle(std::make_shared<Triangle>(v0, v1, v2, mat_ptr));

            // Second triangle
            mesh.add_triangle(std::make_shared<Triangle>(v2, v1, v3, mat_ptr));
        }
    }
}
