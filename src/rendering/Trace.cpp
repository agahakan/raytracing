#include "Trace.hpp"
#include <vector>
#include <thread>
#include <random>
#include <iostream>

void RenderScene(const Scene &scene, Image &image, int canvas_width, int canvas_height)
{
    const Vec3 O(0, 0, 0);
    auto num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0)
        num_threads = 4;
    std::vector<std::thread> threads;
    int rows_per_thread = canvas_height / num_threads;

    auto render = [&](int start_y, int end_y)
    {
        for (int y_pixel = start_y; y_pixel < end_y; ++y_pixel) {
            for (int x_pixel = 0; x_pixel < canvas_width; ++x_pixel) {
                Vec3 D = CanvasToViewport(x_pixel, y_pixel, canvas_width, canvas_height).normalize();
                Ray ray(O, D);
                Color color = TraceRay(ray, 1.0, INF, scene, 0);
                image.SetPixel(x_pixel, y_pixel, color);
            }
        }
    };

    for (unsigned int i = 0; i < num_threads; ++i) {
        int start_y = i * rows_per_thread;
        int end_y = (i == num_threads - 1) ? canvas_height : start_y + rows_per_thread;
        threads.emplace_back(render, start_y, end_y);
    }

    for (auto &thread : threads) {
        thread.join();
    }
}

