#pragma once

#include <memory>

#include "../Material/Material.hpp"
#include "Mesh.hpp"

void generate_sphere_mesh(Mesh &mesh,
                          const Vec3 &center,
                          double radius,
                          int longitude_segments,
                          int latitude_segments,
                          std::shared_ptr<Material> mat_ptr);
