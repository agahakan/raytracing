#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

int main()
{
    // Image dimensions
    const int image_width = 256;
    const int image_height = 256;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
        return 1;
    }

    // Create an SDL window
    SDL_Window *window = SDL_CreateWindow("Gradient Image",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          image_width,
                                          image_height,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    // Create an SDL renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create pixel data for the gradient image
    std::vector<Uint8> pixels(image_width * image_height * 3);  // RGB format

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            auto r = static_cast<Uint8>(255.999 * (double(i) / (image_width - 1)));
            auto g = static_cast<Uint8>(255.999 * (double(j) / (image_height - 1)));
            auto b = 0;

            int pixel_index = (j * image_width + i) * 3;
            pixels[pixel_index] = r;
            pixels[pixel_index + 1] = g;
            pixels[pixel_index + 2] = b;
        }
    }

    // Create an SDL texture and upload the pixel data
    SDL_Texture *texture = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, image_width, image_height);
    if (texture == nullptr) {
        std::cerr << "Texture could not be created! SDL_Error: " << SDL_GetError() << '\n';
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Update the texture with the pixel data
    SDL_UpdateTexture(texture, nullptr, pixels.data(), image_width * 3);

    // Main loop to display the image
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
