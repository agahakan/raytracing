#include <atomic>
#include <fstream>
#include <iostream>
#include <memory>
#include <thread>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "./Backend/SDLGraphics.hpp"
#include "./Camera/Camera.hpp"
#include "./Hittable/Hittable.hpp"
#include "./HittableList/HittableList.hpp"
#include "./Material/Lambertian.hpp"
#include "./Mesh/Mesh.hpp"
#include "./Mesh/SphereMeshGenerator.hpp"
#include "./Mesh/Triangle.hpp"
#include "./Rtweekend/Rtweekend.hpp"

void printVertices(const aiMesh *mesh)
{
    std::cout << "Vertices of mesh " << mesh->mName.C_Str() << ":\n";
    for (unsigned int j = 0; j < mesh->mNumVertices; ++j) {
        const aiVector3D &vertex = mesh->mVertices[j];
        std::cout << "Vertex " << j << ": (" << vertex.x << ", " << vertex.y << ", " << vertex.z
                  << ")\n";
    }
}

int main()
{
    HittableList world;

    // Define the sphere material with your desired color
    auto sphere_material = std::make_shared<Lambertian>(color(1.0, 0.0, 0.0));
    auto sphere_mesh = std::make_shared<Mesh>();
    generate_sphere_mesh(*sphere_mesh, point3(0, 0, -1), 0.5, 20, 20, sphere_material);
    world.add(sphere_mesh);

    Camera cam(16.0 / 9.0, 400, 100);

    cam.set_sky_enabled(true);
    // cam.set_sky_solid_color(color(0.8, 0.8, 0.8));
    cam.set_sky_gradient(color(1.0, 1.0, 1.0), color(0.5, 0.7, 1.0));
    // PRINT MESH
    Assimp::Importer importer;
    const aiScene *scene =
        importer.ReadFile("../assets/model.obj", aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Erreur lors de la chargement du modèle : " << importer.GetErrorString()
                  << std::endl;
        return -1;
    }

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        const aiMesh *mesh = scene->mMeshes[i];
        printVertices(mesh);
    }
    // END PRINT MESH

    Camera cam(16.0 / 9.0, 400, 50);

    SDLGraphics graphics;
    if (!graphics.init("Raytracing C++", cam.image_width, cam.image_height)) {
        return 1;
    }

    std::vector<Uint8> pixels(cam.image_width * cam.image_height * 3, 0);

    std::thread render_thread([&]() { cam.render(world, pixels); });

    bool running = true;
    while (running) {
        running = graphics.processEvents();
        graphics.render(pixels, cam.image_width, cam.image_height);
    }

    render_thread.join();
    graphics.cleanup();

    return 0;
}
