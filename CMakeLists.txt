cmake_minimum_required(VERSION 3.29)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check if we're building for WebAssembly (Wasm)
if(EMSCRIPTEN)
    set(WASM ON)
    set(BUILD_SHARED_LIBS OFF)
endif()

include(FetchContent)

# Fetch nlohmann/json library
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)

FetchContent_MakeAvailable(json)

# Add subdirectories for raymath and rayimage
add_subdirectory(src/raymath)
add_subdirectory(src/rayimage)

# LodePNG library
set(LODEPNG_SRC ${CMAKE_SOURCE_DIR}/src/libs/lodepng/lodepng.cpp)
set(LODEPNG_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/libs/lodepng)

# Gather project sources
file(GLOB PROJECT_SOURCES
    "src/main/*.cpp"
    "src/*.cpp"
    "src/lighting/*.cpp"
    "src/math/*.cpp"
    "src/objects/*.cpp"
    "src/raytracer/*.cpp"
    "src/rendering/*.cpp"
    "src/scene/*.cpp"
    "src/config/*.cpp"
)

# Create the main executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${LODEPNG_SRC})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE raymath rayimage nlohmann_json::nlohmann_json)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${LODEPNG_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/src/raymath
    ${PROJECT_SOURCE_DIR}/src/rayimage
    ${PROJECT_SOURCE_DIR}/src/lighting
    ${PROJECT_SOURCE_DIR}/src/math
    ${PROJECT_SOURCE_DIR}/src/objects
    ${PROJECT_SOURCE_DIR}/src/raytracer
    ${PROJECT_SOURCE_DIR}/src/rendering
    ${PROJECT_SOURCE_DIR}/src/scene
    ${PROJECT_SOURCE_DIR}/src/utils
    ${PROJECT_SOURCE_DIR}/src/config
)

# Compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-fno-exceptions>
    $<$<CXX_COMPILER_ID:Clang>:-fno-exceptions>
    $<$<CXX_COMPILER_ID:MSVC>:/EHs->
)

# WebAssembly specific settings
if(EMSCRIPTEN)
    set(WASM_LINK_FLAGS
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

# WebAssembly build and run target
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

