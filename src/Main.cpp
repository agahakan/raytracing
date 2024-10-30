#include <cmath>
#include <iostream>
#include <limits>
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

    Vec3 operator*(double t) const { return Vec3(x * t, y * t, z * t); }
};

double dot(const Vec3 &a, const Vec3 &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
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

class Scene
{
  public:
    std::vector<Sphere> spheres;
    std::vector<Plane> planes;

    Scene() {};

    void AddSphere(const Sphere &sphere) { spheres.emplace_back(sphere); }
    void AddPlane(const Plane &plane) { planes.emplace_back(plane); }
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

double IntersectRayPlane(const Ray &ray, const Plane &plane)
{
    double denominator = dot(ray.direction, plane.normal);
    if (denominator == 0) {
        return INF;
    }

    double t = -(dot(ray.origin, plane.normal) + plane.distance) / denominator;
    return t;
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
        return closest_sphere->color;
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

    Sphere redSphere(Vec3(0, -1, 3), 1, Color(1, 0, 0));  // ? red sphere
    Sphere blueSphere(Vec3(2, 0, 4), 1, Color(0, 0, 1));  // ? blue sphere
    Sphere greenSphere(Vec3(-2, 0, 4), 1, Color(0, 1, 0));  // ? green sphere
    Plane plane(Vec3(0, 1, 0), 1, Color(1, 1, 1));  // ? white plane

    scene.AddSphere(redSphere);
    scene.AddSphere(blueSphere);
    scene.AddSphere(greenSphere);
    scene.AddPlane(plane);

    const Vec3 O(0, 0, 0);

    for (int y = 0; y < image_height; ++y) {
        for (int x = 0; x < image_width; ++x) {
            double canvas_x = x - image_width / 2.0;
            double canvas_y = -(y - image_height / 2.0);

            Vec3 D = CanvasToViewport(canvas_x, canvas_y, image_width, image_height);
            Ray ray(O, D);
            Color color = TraceRay(ray, 1, INF, scene);

            image.SetPixel(x, y, color);
        }
    }

    const char *filename = "raytraced_scene.png";
    image.WriteFile(filename);
    std::cout << "Image saved as " << filename << std::endl;

    return 0;
}