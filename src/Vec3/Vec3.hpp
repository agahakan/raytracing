#pragma once

#include <cmath>
#include <iostream>

#include "../Utils/Utils.hpp"

class Vec3
{
  public:
    double e[3];

    Vec3();
    Vec3(double x, double y, double z);

    double x() const;
    double y() const;
    double z() const;

    Vec3 operator-() const;
    double operator[](int i) const;
    double &operator[](int i);

    Vec3 &operator+=(const Vec3 &v);
    Vec3 &operator*=(double t);
    Vec3 &operator/=(double t);

    double length() const;
    double length_squared() const;

    static Vec3 random();
    static Vec3 random(double min, double max);
};

using point3 = Vec3;

std::ostream &operator<<(std::ostream &out, const Vec3 &v);
Vec3 operator+(const Vec3 &u, const Vec3 &v);
Vec3 operator-(const Vec3 &u, const Vec3 &v);
Vec3 operator*(const Vec3 &u, const Vec3 &v);
Vec3 operator*(double t, const Vec3 &v);
Vec3 operator*(const Vec3 &v, double t);
Vec3 operator/(const Vec3 &v, double t);
double dot(const Vec3 &u, const Vec3 &v);
Vec3 cross(const Vec3 &u, const Vec3 &v);
Vec3 unit_vector(const Vec3 &v);
Vec3 random_unit_vector();
Vec3 random_on_hemiSphere(const Vec3 &normal);
