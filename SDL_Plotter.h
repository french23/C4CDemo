/*
 * SDL_Plotter.h
 * A simple wrapper for SDL2 to make drawing easier.
 */

#ifndef SDL_PLOTTER_H
#define SDL_PLOTTER_H

// Linux/Standard Include Paths
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

using namespace std;

class SDL_Plotter {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    Uint32 *pixels;
    int row, col;
    bool quit;

public:
    SDL_Plotter(int r, int c) {
        row = r; // Height
        col = c; // Width
        quit = false;

        SDL_Init(SDL_INIT_VIDEO);
        
        // Create Window
        window = SDL_CreateWindow("C4C Holiday Art", 
                                  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                  col, row, SDL_WINDOW_SHOWN);
        
        // Create Renderer
        renderer = SDL_CreateRenderer(window, -1, 0);
        
        // Create Texture
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, 
                                    SDL_TEXTUREACCESS_STATIC, col, row);
        
        // Buffer for pixels
        pixels = new Uint32[col * row];
        
        // Initialize to white
        for(int i = 0; i < col * row; i++) {
            pixels[i] = 0xFFFFFFFF; 
        }
    }

    ~SDL_Plotter() {
        delete[] pixels;
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    // Refresh the screen
    void update() {
        SDL_UpdateTexture(texture, NULL, pixels, col * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    // Check if the user clicked X to close
    bool get_quit() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        return quit;
    }

    // Draw a single pixel
    void plot_point(int x, int y, int r, int g, int b) {
        if (x >= 0 && x < col && y >= 0 && y < row) {
            Uint32 color = (255 << 24) | (r << 16) | (g << 8) | b;
            pixels[y * col + x] = color;
        }
    }
    
    // Wait for milliseconds
    void Sleep(int ms) {
        SDL_Delay(ms);
    }
    
    // Check for keyboard hit (simplified)
    bool kbhit() {
        // Simplified for this challenge; mostly handled by get_quit event loop
        return false; 
    }
};

#endif