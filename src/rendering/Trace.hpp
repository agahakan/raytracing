#pragma once

#include "Utility.hpp"
#include "../math/Vec3.hpp"
#include "../raytracer/Ray.hpp"
#include "../scene/Scene.hpp"
#include "Render.hpp"
#include "../rayimage/Image.hpp"

void RenderScene(const Scene &scene, Image &image, int canvas_width, int canvas_height);
