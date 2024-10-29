#pragma once

#include <limits>

class Interval
{
  public:
    double min, max;

    Interval()
        : min(+std::numeric_limits<double>::infinity())
        , max(-std::numeric_limits<double>::infinity())
    {
    }

    Interval(double min, double max)
        : min(min)
        , max(max)
    {
    }

    double size() const { return max - min; }

    bool contains(double x) const { return min <= x && x <= max; }

    bool surrounds(double x) const { return min < x && x < max; }

    double clamp(double x) const
    {
        if (x < min)
            return min;
        if (x > max)
            return max;
        return x;
    }

    static const Interval empty;
    static const Interval universe;
};
