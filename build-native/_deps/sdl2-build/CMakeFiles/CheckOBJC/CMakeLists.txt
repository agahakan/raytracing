cmake_minimum_required(VERSION 3.30.5)
set(CMAKE_MODULE_PATH "/Users/G0512/Dev/HETIC/RayTracer/raytracing/build-native/_deps/sdl2-src/cmake")
project(CheckOBJC OBJC)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/result.cmake"
  "set(CMAKE_OBJC_COMPILER \"${CMAKE_OBJC_COMPILER}\")\n"
  
  )