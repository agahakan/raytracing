#include "Vec3.hpp"

Vec3::Vec3(double x_, double y_, double z_)
    : x(x_), y(y_), z(z_) {}

Vec3 Vec3::operator+(const Vec3 &v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
Vec3 Vec3::operator-(const Vec3 &v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
Vec3 Vec3::operator*(double t) const { return Vec3(x * t, y * t, z * t); }
Vec3 Vec3::operator/(double t) const { return Vec3(x / t, y / t, z / t); }
Vec3 Vec3::operator-() const { return Vec3(-x, -y, -z); }

Vec3 Vec3::normalize() const
{
    double len = std::sqrt(x * x + y * y + z * z);
    return Vec3(x / len, y / len, z / len);
}

double dot(const Vec3 &a, const Vec3 &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double length(const Vec3 &v)
{
    return std::sqrt(dot(v, v));
}

