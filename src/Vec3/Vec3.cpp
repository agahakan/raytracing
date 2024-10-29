#include "Vec3.hpp"

Vec3::Vec3()
    : e {0, 0, 0}
{
}

Vec3::Vec3(double x, double y, double z)
    : e {x, y, z}
{
}

double Vec3::x() const
{
    return e[0];
}

double Vec3::y() const
{
    return e[1];
}

double Vec3::z() const
{
    return e[2];
}

Vec3 Vec3::operator-() const
{
    return Vec3(-e[0], -e[1], -e[2]);
}

double Vec3::operator[](int i) const
{
    return e[i];
}

double &Vec3::operator[](int i)
{
    return e[i];
}

Vec3 &Vec3::operator+=(const Vec3 &v)
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

Vec3 &Vec3::operator*=(double t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

Vec3 &Vec3::operator/=(double t)
{
    return *this *= 1 / t;
}

double Vec3::length() const
{
    return std::sqrt(length_squared());
}

double Vec3::length_squared() const
{
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

Vec3 Vec3::random()
{
    return Vec3(random_double(), random_double(), random_double());
}

Vec3 Vec3::random(double min, double max)
{
    return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

std::ostream &operator<<(std::ostream &out, const Vec3 &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

Vec3 operator+(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

Vec3 operator-(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

Vec3 operator*(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

Vec3 operator*(double t, const Vec3 &v)
{
    return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

Vec3 operator*(const Vec3 &v, double t)
{
    return t * v;
}

Vec3 operator/(const Vec3 &v, double t)
{
    return (1 / t) * v;
}

double dot(const Vec3 &u, const Vec3 &v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

Vec3 cross(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

Vec3 unit_vector(const Vec3 &v)
{
    return v / v.length();
}

Vec3 random_unit_vector()
{
    while (true) {
        auto p = Vec3::random(-1, 1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1)
            return p / std::sqrt(lensq);
    }
}

Vec3 random_on_hemiSphere(const Vec3 &normal)
{
    Vec3 on_unit_Sphere = random_unit_vector();
    if (dot(on_unit_Sphere, normal) > 0.0)
        return on_unit_Sphere;
    else
        return -on_unit_Sphere;
}
