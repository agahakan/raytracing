// src/Main.cpp

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <thread>
#include <vector>

#include "Image.hpp"

const double INF = std::numeric_limits<double>::infinity();

struct Vec3
{
    double x, y, z;

    Vec3(double x_ = 0, double y_ = 0, double z_ = 0)
        : x(x_)
        , y(y_)
        , z(z_)
    {
    }

    Vec3 operator+(const Vec3 &v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator-(const Vec3 &v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator*(double t) const { return Vec3(x * t, y * t, z * t); }
    Vec3 operator/(double t) const { return Vec3(x / t, y / t, z / t); }

    Vec3 operator-() const { return Vec3(-x, -y, -z); }

    Vec3 normalize() const
    {
        double len = std::sqrt(x * x + y * y + z * z);
        return Vec3(x / len, y / len, z / len);
    }
};

double dot(const Vec3 &a, const Vec3 &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double length(const Vec3 &v)
{
    return std::sqrt(dot(v, v));
}

enum class LightType
{
    Ambient,
    Point,
    Directional
};

struct Light
{
    LightType type;
    double intensity;
    Vec3 position;

    Light(LightType type_, double intensity_)
        : type(type_)
        , intensity(intensity_)
        , position(0, 0, 0)
    {
    }

    Light(LightType type_, double intensity_, const Vec3 &vec)
        : type(type_)
        , intensity(intensity_)
        , position(vec)
    {
    }
};

struct Ray
{
    Vec3 origin;
    Vec3 direction;

    Ray(const Vec3 &origin_, const Vec3 &direction_)
        : origin(origin_)
        , direction(direction_.normalize())
    {
    }
};

struct Object
{
    Color color;
    double reflection;

    Object(const Color &col, double reflection_ = 0.0)
        : color(col)
        , reflection(reflection_)
    {
    }

    virtual double Intersect(const Ray &ray, double t_min, double t_max) const = 0;
    virtual Vec3 getNormal(const Vec3 &P) const = 0;
    virtual ~Object() = default;
};

struct Sphere : public Object
{
    Vec3 center;
    double radius;

    Sphere(const Vec3 &c, double r, const Color &col, double reflection_ = 0.0)
        : Object(col, reflection_)
        , center(c)
        , radius(r)
    {
    }

    double Intersect(const Ray &ray, double t_min, double t_max) const override
    {
        Vec3 CO = ray.origin - center;
        double a = dot(ray.direction, ray.direction);
        double b = 2.0 * dot(CO, ray.direction);
        double c = dot(CO, CO) - radius * radius;
        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return INF;
        }

        double sqrt_discriminant = std::sqrt(discriminant);
        double t1 = (-b + sqrt_discriminant) / (2.0 * a);
        double t2 = (-b - sqrt_discriminant) / (2.0 * a);

        if (t1 >= t_min && t1 <= t_max) {
            return t1;
        }

        if (t2 >= t_min && t2 <= t_max) {
            return t2;
        }

        return INF;
    }

    Vec3 getNormal(const Vec3 &P) const override { return (P - center).normalize(); }
};

struct Plane : public Object
{
    Vec3 c;
    Vec3 n;

    Plane(const Vec3 &c_, const Vec3 &n_, const Color &col, double reflection_ = 0.0)
        : Object(col, reflection_)
        , c(c_)
        , n(n_.normalize())
    {
    }

    double Intersect(const Ray &ray, double t_min, double t_max) const override
    {
        double denom = dot(ray.direction, n);

        if (std::abs(denom) < 1e-6) {
            return INF;
        }

        double num = dot(c - ray.origin, n);
        double t = num / denom;

        if (t >= t_min && t <= t_max) {
            return t;
        }

        return INF;
    }

    Vec3 getNormal(const Vec3 &P) const override { return n; }
};

class Scene
{
  public:
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<Light> lights;

    Scene() = default;

    void AddObject(const std::shared_ptr<Object> &object) { objects.emplace_back(object); }
    void AddLight(const Light &light) { lights.emplace_back(light); }
};

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

int main()
{
    const int canvas_width = 1920;
    const int canvas_height = 1080;
    Image image(canvas_width, canvas_height);
    Scene scene;

    const int grid_size = 6;
    const double spacing = 2.5;
    const double amplitude = 1.0;
    const double frequency = 0.5;

    const double min_y_offset = 1.0;
    const double min_z = 6.0;
    const double base_z = min_z + grid_size * spacing;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = -grid_size; i <= grid_size; ++i) {
        for (int j = -grid_size; j <= grid_size; ++j) {
            double x = i * spacing;
            double z = j * spacing + base_z;
            double wave_value = sin(frequency * (x + z));
            double y = amplitude * wave_value + min_y_offset;
            double r = dis(gen);
            double g = dis(gen);
            double b = dis(gen);
            Color color(r, g, b);
            double reflection = 0.2;
            auto sphere = std::make_shared<Sphere>(Vec3(x, y, z), 1.0, color, reflection);
            scene.AddObject(sphere);
        }
    }

    std::shared_ptr<Object> groundPlane =
        std::make_shared<Plane>(Vec3(0, -1, 0), Vec3(0, 1, 0), Color(1, 1, 1), 0.5);
    scene.AddObject(groundPlane);

    scene.AddLight(Light(LightType::Ambient, 0.2));
    scene.AddLight(Light(LightType::Point, 2.8, Vec3(2, 1, 0)));
    scene.AddLight(Light(LightType::Directional, 0.2, Vec3(1, 4, 4)));

    const Vec3 O(0, 0, 0);

    auto num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0)
        num_threads = 4;
    std::vector<std::thread> threads;
    int rows_per_thread = canvas_height / num_threads;

    auto render = [&](int start_y, int end_y)
    {
        for (int y_pixel = start_y; y_pixel < end_y; ++y_pixel) {
            for (int x_pixel = 0; x_pixel < canvas_width; ++x_pixel) {
                Vec3 D =
                    CanvasToViewport(x_pixel, y_pixel, canvas_width, canvas_height).normalize();
                Ray ray(O, D);
                Color color = TraceRay(ray, 1.0, INF, scene, 0);
                image.SetPixel(x_pixel, y_pixel, color);
            }
        }
    };

    for (unsigned int i = 0; i < num_threads; ++i) {
        int start_y = i * rows_per_thread;
        int end_y = (i == num_threads - 1) ? canvas_height : start_y + rows_per_thread;
        threads.emplace_back(render, start_y, end_y);
    }

    for (auto &thread : threads) {
        thread.join();
    }

    const char *filename = "raytraced_wave_field.png";
    image.WriteFile(filename);
    std::cout << "Image saved as " << filename << std::endl;

    return 0;
}
