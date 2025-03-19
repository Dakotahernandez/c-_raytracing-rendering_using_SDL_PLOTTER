#include <SDL2/SDL.h>
#include <iostream>
#include "RayTracer.h"
#include "Vec3.h"

// Map mouse coordinates to a world-space light position.
// The light moves on the plane z = -2.
static Vec3 mapMouseToWorld(int mouseX, int mouseY, int screenWidth, int screenHeight) {
    double rangeX = 4.0;  // x ∈ [-2, 2]
    double rangeY = 3.0;  // y ∈ [-1.5, 1.5]
    
    double worldX = (double(mouseX) / double(screenWidth)) * rangeX - (rangeX / 2.0);
    double worldY = -((double(mouseY) / double(screenHeight)) * rangeY - (rangeY / 2.0));
    double worldZ = -2.0;
    
    return Vec3(worldX, worldY, worldZ);
}

int main(int argc, char* argv[]) {
    const int width = 800;
    const int height = 600;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return 1;
    }
    
    SDL_Window* window = SDL_CreateWindow("Interactive Ray Tracer",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    SDL_Texture* texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STATIC,
                                             width, height);
    if (!texture) {
        std::cerr << "Texture could not be created! SDL_Error: " << SDL_GetError() << "\n";
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // Allocate pixel buffer
    uint32_t* pixels = new uint32_t[width * height];
    
    // Create our ray tracer and set an initial light position.
    RayTracer tracer(width, height);
    Vec3 lightPos(0.0, 0.0, -2.0);
    tracer.setLightPosition(lightPos);
    
    // Variables to track mouse position (initialize to center)
    int mouseX = width / 2;
    int mouseY = height / 2;
    
    bool quit = false;
    SDL_Event e;
    
    while (!quit) {
        // Process events.
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_MOUSEMOTION) {
                // Update mouse position and light position.
                mouseX = e.motion.x;
                mouseY = e.motion.y;
                Vec3 newLightPos = mapMouseToWorld(e.motion.x, e.motion.y, width, height);
                tracer.setLightPosition(newLightPos);
            }
        }
        
        // Render the scene.
        tracer.render(pixels);
        SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(uint32_t));
        
        // Clear the renderer and copy the texture.
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        
        // Draw a green line from the center of the sphere (screen center) to the mouse position.
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green color
        SDL_RenderDrawLine(renderer, width / 2, height / 2, mouseX, mouseY);
        
        // Present the updated renderer.
        SDL_RenderPresent(renderer);
    }
    
    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}

