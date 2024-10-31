#include <algorithm>

#include "Render.hpp"

Vec3 Reflect(const Vec3 &I, const Vec3 &N)
{
    return N * (2.0 * dot(N, I)) - I;
}

double ComputeLighting(const Vec3 &P, const Vec3 &N, const Vec3 &V, const Scene &scene)
{
    double i = 0.0;

    for (const auto &light : scene.lights) {
        if (light.type == LightType::Ambient) {
            i += light.intensity;
            continue;
        }

        Vec3 L;
        double max_distance = INF;

        if (light.type == LightType::Point) {
            L = light.position - P;
            max_distance = length(L);
            L = L / max_distance;
        } else if (light.type == LightType::Directional) {
            L = light.position.normalize();
            max_distance = INF;
        }

        Ray shadow_ray(P + N * 1e-4, L);
        bool in_shadow = false;

        for (const auto &object : scene.objects) {
            double t = object->Intersect(shadow_ray, 1e-4, max_distance);
            if (t < max_distance) {
                in_shadow = true;
                break;
            }
        }

        if (!in_shadow) {
            double n_dot_l = dot(N, L);
            if (n_dot_l > 0) {
                i += light.intensity * n_dot_l / (length(N) * length(L));
            }
        }
    }

    i = std::min(i, 1.0);

    return i;
}

Color TraceRay(const Ray &ray, double t_min, double t_max, const Scene &scene, int depth)
{
    if (depth > 3) {
        return Color(0, 0, 0);
    }

    double closest_t = INF;
    const Object *closest_object = nullptr;

    for (const auto &object : scene.objects) {
        double t = object->Intersect(ray, t_min, closest_t);
        if (t < closest_t) {
            closest_t = t;
            closest_object = object.get();
        }
    }

    if (!closest_object) {
        return Color(0, 0, 0);
    }

    Vec3 P = ray.origin + ray.direction * closest_t;
    Vec3 N = closest_object->getNormal(P);

    Vec3 V = ray.direction * -1;

    double intensity = ComputeLighting(P, N, V, scene);
    Color object_color = closest_object->color * intensity;

    if (closest_object->reflection > 0.0) {
        Vec3 R_dir = Reflect(ray.direction, N).normalize();
        Ray reflection_ray(P + N * 1e-4, R_dir);
        Color reflection_color = TraceRay(reflection_ray, 1e-4, INF, scene, depth + 1);
        object_color = object_color * (1.0 - closest_object->reflection)
            + reflection_color * closest_object->reflection;
    }

    return object_color;
}

Vec3 CanvasToViewport(int x, int y, int canvas_width, int canvas_height)
{
    double aspect_ratio = static_cast<double>(canvas_width) / static_cast<double>(canvas_height);
    double viewport_height = 1.0;
    double viewport_width = aspect_ratio * viewport_height;
    double projection_plane_d = 1.0;

    double normalized_x = (static_cast<double>(x) + 0.5 - static_cast<double>(canvas_width) / 2.0)
        / (static_cast<double>(canvas_width) / 2.0);
    double normalized_y =
        (static_cast<double>(canvas_height) / 2.0 - (static_cast<double>(y) + 0.5))
        / (static_cast<double>(canvas_height) / 2.0);

    return Vec3(normalized_x * viewport_width, normalized_y * viewport_height, projection_plane_d);
}
