#include <chrono>
#include <cmath>
#include <iostream>
#include <limits>
#include <thread>
#include <vector>

#include "Image.hpp"

const double INF = std::numeric_limits<double>::infinity();

struct Vec3
{
    double x, y, z;

    Vec3(double x = 0, double y = 0, double z = 0)
        : x(x)
        , y(y)
        , z(z)
    {
    }

    Vec3 operator-(const Vec3 &v) const { return Vec3(x - v.x, y - v.y, z - v.z); }

    Vec3 operator+(const Vec3 &v) const { return Vec3(x + v.x, y + v.y, z + v.z); }

    Vec3 operator*(double t) const { return Vec3(x * t, y * t, z * t); }

    Vec3 operator/(double t) const { return Vec3(x / t, y / t, z / t); }
};

double dot(const Vec3 &a, const Vec3 &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double length(const Vec3 &v)
{
    return std::sqrt(dot(v, v));
}

struct Sphere
{
    Vec3 center;
    double radius;
    Color color;

    Sphere(const Vec3 &c, double r, const Color &col)
        : center(c)
        , radius(r)
        , color(col)
    {
    }
};

struct Plane
{
    Vec3 normal;
    double distance;
    Color color;

    Plane(const Vec3 &n, double d, const Color &col)
        : normal(n)
        , distance(d)
        , color(col)
    {
    }
};

struct Light
{
    enum Type
    {
        AMBIENT,
        POINT,
        DIRECTIONAL
    } type;
    double intensity;
    Vec3 position;  // ? Used only for point lights
    Vec3 direction;  // ? Used only for directional lights

    Light(Type t, double intensity, const Vec3 &pos = Vec3(), const Vec3 &dir = Vec3())
        : type(t)
        , intensity(intensity)
        , position(pos)
        , direction(dir)
    {
    }
};

class Scene
{
  public:
    std::vector<Sphere> spheres;
    std::vector<Plane> planes;
    std::vector<Light> lights;

    Scene() {};

    void AddSphere(const Sphere &sphere) { spheres.emplace_back(sphere); }
    void AddPlane(const Plane &plane) { planes.emplace_back(plane); }
    void AddLight(const Light &light) { lights.emplace_back(light); }
};

struct Ray
{
    Vec3 origin;
    Vec3 direction;

    Ray(const Vec3 &origin, const Vec3 &direction)
        : origin(origin)
        , direction(direction)
    {
    }
};

// INTERSECT RAY WITH SPHERE
std::pair<double, double> IntersectRaySphere(const Ray &ray, const Sphere &sphere)
{
    Vec3 CO = ray.origin - sphere.center;
    double a = dot(ray.direction, ray.direction);  // ? dot product
    double b = 2 * dot(CO, ray.direction);  // ? dot product
    double c = dot(CO, CO) - sphere.radius * sphere.radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return {INF, INF};
    }

    double sqrt_discriminant = std::sqrt(discriminant);
    double t1 = (-b + sqrt_discriminant) / (2 * a);
    double t2 = (-b - sqrt_discriminant) / (2 * a);
    return {t1, t2};
}

// INTERSECT RAY WITH PLANE
double IntersectRayPlane(const Ray &ray, const Plane &plane)
{
    double denominator = dot(ray.direction, plane.normal);
    if (denominator == 0) {
        return INF;
    }

    double t = -(dot(ray.origin, plane.normal) + plane.distance) / denominator;
    return t;
}

// COMPUTE LIGHTING
double ComputeLighting(const Vec3 &P, const Vec3 &N, const Scene &scene)
{
    double i = 0.0;

    for (const auto &light : scene.lights) {
        if (light.type == Light::AMBIENT) {
            i += light.intensity;
        } else {
            Vec3 L;
            if (light.type == Light::POINT) {
                L = light.position - P;
            } else {
                L = light.direction;
            }

            double n_dot_l = dot(N, L);
            if (n_dot_l > 0) {
                i += light.intensity * n_dot_l / (length(N) * length(L));
            }
        }
    }
    return i;
}

// TRACE RAY AND RETURN COLOR
Color TraceRay(const Ray &ray, double t_min, double t_max, const Scene &scene)
{
    double closest_t = INF;
    const Sphere *closest_sphere = nullptr;
    const Plane *closest_plane = nullptr;

    for (const auto &sphere : scene.spheres) {
        auto [t1, t2] = IntersectRaySphere(ray, sphere);
        if (t1 >= t_min && t1 <= t_max && t1 < closest_t) {
            closest_t = t1;
            closest_sphere = &sphere;
        }
        if (t2 >= t_min && t2 <= t_max && t2 < closest_t) {
            closest_t = t2;
            closest_sphere = &sphere;
        }
    }

    for (const auto &plane : scene.planes) {
        double t = IntersectRayPlane(ray, plane);
        if (t >= t_min && t <= t_max && t < closest_t) {
            closest_t = t;
            closest_plane = &plane;
        }
    }

    if (closest_plane) {
        return closest_plane->color;
    }

    if (closest_sphere) {
        Vec3 P = ray.origin + ray.direction * closest_t;
        Vec3 N = P - closest_sphere->center;
        N = N / length(N);
        double intensity = ComputeLighting(P, N, scene);
        return closest_sphere->color * intensity;
    }

    return Color(0.2, 0.2, 0.2);
}

// CONVERT SCREEN COORDINATES TO VIEWPORT COORDINATES
Vec3 CanvasToViewport(int x, int y, int image_width, int image_height)
{
    double viewport_size = 1.0;  // ? viewport ration (1.0 = 100% = image size)
    double projection_plane_d = 1.0;  // ? distance projection (z coordinate)

    return Vec3(x * viewport_size / image_width,  // ? convert x to viewport coordinates
                y * viewport_size / image_height,  // ? convert y to viewport coordinates
                projection_plane_d);
}

int main()
{
    const int image_width = 800;
    const int image_height = 800;
    Image image(image_width, image_height);

    Scene scene;

    Light ambientLight(Light::AMBIENT, 0.2);  // ? ambient light
    Light pointLight(Light::POINT, 0.6, Vec3(2, 1, 0));  // ? point light
    Light directionalLight(Light::DIRECTIONAL, 0.2, Vec3(), Vec3(1, 4, 4));  // ? directional light

    Sphere redSphere(Vec3(0, -0.8, 3), 1, Color(1, 0, 0));  // ? red sphere
    Sphere blueSphere(Vec3(2, 0, 4), 1, Color(0, 0, 1));  // ? blue sphere
    Sphere greenSphere(Vec3(-2, 0, 4), 1, Color(0, 1, 0));  // ? green sphere
    Plane plane(Vec3(0, 1, 0), 1, Color(1, 1, 1));  // ? white plane

    scene.AddSphere(redSphere);
    scene.AddSphere(blueSphere);
    scene.AddSphere(greenSphere);
    scene.AddLight(ambientLight);
    scene.AddLight(pointLight);
    scene.AddLight(directionalLight);
    scene.AddPlane(plane);

    const Vec3 O(0, 0, 0);

    auto start_time = std::chrono::high_resolution_clock::now();

    // for (int y = 0; y < image_height; ++y) {
    //     for (int x = 0; x < image_width; ++x) {
    //         double canvas_x = x - image_width / 2.0;
    //         double canvas_y = -(y - image_height / 2.0);

    //         Vec3 D = CanvasToViewport(canvas_x, canvas_y, image_width, image_height);
    //         Ray ray(O, D);
    //         Color color = TraceRay(ray, 1, INF, scene);

    //         image.SetPixel(x, y, color);
    //     }
    // }

    const int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(num_threads);

    for (int t = 0; t < num_threads; ++t) {
        threads[t] = std::thread(
            [&, t]()
            {
                for (int y = t; y < image_height; y += num_threads) {
                    for (int x = 0; x < image_width; ++x) {
                        double canvas_x = x - image_width / 2.0;
                        double canvas_y = -(y - image_height / 2.0);

                        Vec3 D = CanvasToViewport(canvas_x, canvas_y, image_width, image_height);
                        Ray ray(O, D);
                        Color color = TraceRay(ray, 1, INF, scene);

                        image.SetPixel(x, y, color);
                    }
                }
            });
    }

    for (auto &t : threads) {
        t.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    const char *filename = "raytraced_scene.png";
    image.WriteFile(filename);
    std::cout << "Image saved as " << filename << std::endl;

    std::cout << "Elapsed time: " << elapsed.count() << "s" << std::endl;

    return 0;
}
