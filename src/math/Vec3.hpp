#pragma once

#include <cmath>

struct Vec3
{
    double x, y, z;

    Vec3(double x_ = 0, double y_ = 0, double z_ = 0);
    
    Vec3 operator+(const Vec3 &v) const;
    Vec3 operator-(const Vec3 &v) const;
    Vec3 operator*(double t) const;
    Vec3 operator/(double t) const;
    Vec3 operator-() const;
    Vec3 normalize() const;
};

double dot(const Vec3 &a, const Vec3 &b);
double length(const Vec3 &v);
