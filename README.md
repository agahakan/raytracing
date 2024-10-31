# Ray Tracing Engine

---

## Description

This project is a ray tracing engine written in C++. It allows the generation of 3D images by simulating the behavior of light in a scene containing spheres and planes. The engine handles different types of lights, including ambient, point, and directional lights.

## Installation & Run

Creating the necessary folders for native builds:

```bash
mkdir build-native
```

###### For Build

```bash
cd build-native
cmake ..
cmake --build . --target run
```

Once executed, the program generates an image called raytraced_scene.png that represents the 3D scene with the defined objects and lights.

## Auteurs

- [Hakan Arik](https://github.com/agahakan)
- [Matteo Courquin](https://github.com/MatteoCourquin)
