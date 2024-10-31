#pragma once

#include "Vec3.hpp"
#include "Scene.hpp"
#include "Object.hpp"
#include "Ray.hpp"
#include "Image.hpp"
#include "Utility.hpp"

Color TraceRay(const Ray &ray, double t_min, double t_max, const Scene &scene, int depth);
Vec3 Reflect(const Vec3 &I, const Vec3 &N);
double ComputeLighting(const Vec3 &P, const Vec3 &N, const Vec3 &V, const Scene &scene);
Vec3 CanvasToViewport(int x, int y, int canvas_width, int canvas_height);
