#pragma once

#include <memory>
#include <vector>

#include "../Hittable/Hittable.hpp"
#include "../Interval/Interval.hpp"

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable
{
  public:
    std::vector<shared_ptr<Hittable>> objects;

    HittableList();
    HittableList(shared_ptr<Hittable> object);
    void clear();
    void add(shared_ptr<Hittable> object);
    bool hit(const Ray &r, Interval Ray_t, HitRecord &rec) const override;
};
