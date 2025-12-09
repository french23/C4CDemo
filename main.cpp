//=========================================
// C4C HOLIDAY PLOTTER
// Challenge: Festive Console Art
//=========================================

#include <iostream>
#include <cmath>
#include "SDL_Plotter.h"

using namespace std;

// GLOBAL CONSTANTS FOR WINDOW SIZE
// We define these here so we can check bounds inside our functions
const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;

// 1. Color Struct
struct Color {
    int R, G, B;
    Color(int r = 0, int g = 0, int b = 0) {
        R = r; G = g; B = b;
    }
};

// 2. Function Prototypes
void draw_circle(SDL_Plotter& p, int centerX, int centerY, int radius, Color c);
void fill_circle(SDL_Plotter& p, int centerX, int centerY, int radius, Color c);
void draw_rect(SDL_Plotter& p, int x, int y, int width, int height, Color c);
void fill_rect(SDL_Plotter& p, int x, int y, int width, int height, Color c);
void draw_line(SDL_Plotter& p, int x1, int y1, int x2, int y2, Color c);

//=========================================
// MAIN FUNCTION
//=========================================
int main(int argc, char** argv) {
    // Note: SDL_Plotter constructor often takes (ROW, COL). 
    SDL_Plotter g(WIN_HEIGHT, WIN_WIDTH); 

    // Define some colors
    Color red(255, 0, 0);
    Color green(0, 255, 0);
    Color blue(0, 0, 255);
    Color yellow(255, 255, 0);
    Color white(255, 255, 255);

    // --- DEMO AREA ---

    // 1. Fill Circle (Face base)
    fill_circle(g, 400, 300, 100, yellow);

    // 2. Draw Circle (Outline)
    draw_circle(g, 400, 300, 100, red);

    // 3. Fill Rectangle (Eyes)
    fill_rect(g, 350, 270, 20, 20, blue);
    fill_rect(g, 430, 270, 20, 20, blue);

    // 4. Draw Rectangle (Glasses frames)
    draw_rect(g, 345, 265, 30, 30, red);
    draw_rect(g, 425, 265, 30, 30, red);

    // 5. Draw Line (Bridge of glasses and a mouth)
    draw_line(g, 375, 280, 425, 280, red); // Bridge
    draw_line(g, 370, 350, 430, 350, red); // Mouth

    // Update screen
    g.update();

    // Main Loop: Keeps the window open
    while (!g.get_quit()) {
        // Just wait
    }
    
    return 0;
}

//=========================================
// FUNCTION DEFINITIONS
//=========================================

// Outline a circle
void draw_circle(SDL_Plotter& p, int centerX, int centerY, int radius, Color c) {
    for (int angle = 0; angle < 360; angle += 1) {
        double rad = angle * M_PI / 180.0;
        int x = (int)(centerX + radius * cos(rad));
        int y = (int)(centerY + radius * sin(rad));
        
        // Fixed bounds check using global constants
        if(x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT){
            p.plot_point(x, y, c.R, c.G, c.B);
        }
    }
}

// Fill a circle solid
void fill_circle(SDL_Plotter& p, int centerX, int centerY, int radius, Color c) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                int plotX = centerX + x;
                int plotY = centerY + y;
                
                // Fixed bounds check using global constants
                if(plotX >= 0 && plotX < WIN_WIDTH && plotY >= 0 && plotY < WIN_HEIGHT){
                     p.plot_point(plotX, plotY, c.R, c.G, c.B);
                }
            }
        }
    }
}

// Outline a rectangle
void draw_rect(SDL_Plotter& p, int x, int y, int width, int height, Color c) {
    // Top and Bottom
    for (int i = 0; i < width; i++) {
        if (x + i < WIN_WIDTH && y < WIN_HEIGHT) 
            p.plot_point(x + i, y, c.R, c.G, c.B);
        if (x + i < WIN_WIDTH && y + height < WIN_HEIGHT) 
            p.plot_point(x + i, y + height, c.R, c.G, c.B);
    }
    // Left and Right
    for (int i = 0; i < height; i++) {
        if (x < WIN_WIDTH && y + i < WIN_HEIGHT)
            p.plot_point(x, y + i, c.R, c.G, c.B);
        if (x + width < WIN_WIDTH && y + i < WIN_HEIGHT)
            p.plot_point(x + width, y + i, c.R, c.G, c.B);
    }
}

// Fill a rectangle solid
void fill_rect(SDL_Plotter& p, int x, int y, int width, int height, Color c) {
    for (int r = 0; r < height; r++) {
        for (int col = 0; col < width; col++) {
            int plotX = x + col;
            int plotY = y + r;
            if (plotX >= 0 && plotX < WIN_WIDTH && plotY >= 0 && plotY < WIN_HEIGHT) {
                p.plot_point(plotX, plotY, c.R, c.G, c.B);
            }
        }
    }
}

// Bresenham's Line Algorithm
void draw_line(SDL_Plotter& p, int x1, int y1, int x2, int y2, Color c) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        if (x1 >= 0 && x1 < WIN_WIDTH && y1 >= 0 && y1 < WIN_HEIGHT) {
            p.plot_point(x1, y1, c.R, c.G, c.B);
        }

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}
