#pragma once

#include "Mesh.hpp"

void generate_sphere_mesh(Mesh& mesh, const point3& center, double radius,
                          int longitude_segments, int latitude_segments);

