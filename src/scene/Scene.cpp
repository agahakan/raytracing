#include "Scene.hpp"

void Scene::AddObject(const std::shared_ptr<Object> &object)
{
    objects.emplace_back(object);
}

void Scene::AddLight(const Light &light)
{
    lights.emplace_back(light);
}

