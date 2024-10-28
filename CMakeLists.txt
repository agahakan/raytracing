cmake_minimum_required(VERSION 3.29)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check if we're building for Wasm
if(EMSCRIPTEN)
    set(WASM ON)
    set(BUILD_SHARED_LIBS OFF)
    set(SDL_SHARED OFF CACHE BOOL "Build SDL shared library" FORCE)
    set(SDL_STATIC ON CACHE BOOL "Build SDL static library" FORCE)
endif()

include(FetchContent)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.8
)
FetchContent_MakeAvailable(SDL2)

file(GLOB PROJECT_SOURCES 
    "src/Backend/*.cpp"
    "src/Backend/*.hpp"
    "src/Camera/*.cpp"
    "src/Camera/*.hpp"
    "src/Color/*.cpp"
    "src/Color/*.hpp"
    "src/Hittable/*.cpp"
    "src/Hittable/*.hpp"
    "src/HittableList/*.cpp"
    "src/HittableList/*.hpp"
    "src/Interval/*.cpp"
    "src/Interval/*.hpp"
    "src/Ray/*.cpp"
    "src/Ray/*.hpp"
    "src/Rtweekend/*.cpp"
    "src/Rtweekend/*.hpp"
    "src/Sphere/*.cpp"
    "src/Sphere/*.hpp"
    "src/Vec3/*.cpp"
    "src/Vec3/*.hpp"
    "src/Main.cpp"
)

# Create the main executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

# Compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-fno-exceptions>
    $<$<CXX_COMPILER_ID:Clang>:-fno-exceptions>
    $<$<CXX_COMPILER_ID:MSVC>:/EHs->
)

# WebAssembly specific settings
if(EMSCRIPTEN)
    set(WASM_LINK_FLAGS
        "-s USE_SDL=2"
        "-s WASM=1"
        "-s ALLOW_MEMORY_GROWTH=1"
        "-s EXPORTED_RUNTIME_METHODS=['cwrap']"
        "-s EXPORTED_FUNCTIONS=['_main']"
        "-s NO_EXIT_RUNTIME=1"
        "-s ASSERTIONS=1"
    )
    
    # Only add assets preloading if the directory exists
    if(EXISTS "${CMAKE_SOURCE_DIR}/assets")
        list(APPEND WASM_LINK_FLAGS "--preload-file ${CMAKE_SOURCE_DIR}/assets@/assets")
    endif()
    
    string(REPLACE ";" " " WASM_LINK_FLAGS_STR "${WASM_LINK_FLAGS}")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "${WASM_LINK_FLAGS_STR}")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Native build and run target
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${PROJECT_NAME} -- -j 8
    COMMAND ${CMAKE_COMMAND} -E echo "Running executable..."
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    USES_TERMINAL
)

# Wasm build and run target
if(EMSCRIPTEN)
    add_custom_target(run-wasm
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${PROJECT_NAME} -- -j 8
        COMMAND ${CMAKE_COMMAND} -E echo "Starting Emscripten HTTP server..."
        COMMAND emrun --no_browser --port 8080 ${PROJECT_NAME}.html
        DEPENDS ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        USES_TERMINAL
    )
endif()