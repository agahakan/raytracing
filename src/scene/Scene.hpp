#pragma once

#include <vector>
#include <memory>
#include "../objects/Object.hpp"
#include "../lighting/Light.hpp"

class Scene
{
public:
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<Light> lights;

    Scene() = default;

    void AddObject(const std::shared_ptr<Object> &object);
    void AddLight(const Light &light);
};

