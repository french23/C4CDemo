//=========================================
// C4C HOLIDAY PLOTTER STARTER CODE
// Challenge: Festive Console Art
//=========================================

#include <iostream>
#include <cmath> // For sin() and cos()

// **NOTE:** The actual SDL Plotter library includes are highly specific.
// Assuming the environment is set up with a master header like "SDL_Plotter.h"
#include "SDL_Plotter.h"

using namespace std;

// Function to draw a point (wrapper for the SDL Plotter)
void plot_point(int x, int y, int r, int g, int b, SDL_Plotter& g);

//---------------------------------------------------------
// Draw a basic circle using trigonometry
//---------------------------------------------------------
void draw_circle(SDL_Plotter& g, int centerX, int centerY, int radius, int R, int G, int B) {
    for (int angle = 0; angle < 360; angle += 1) {
        // Convert angle to radians
        double rad = angle * M_PI / 180.0;

        // Calculate (x, y) coordinates on the circle perimeter
        int x = (int)(centerX + radius * cos(rad));
        int y = (int)(centerY + radius * sin(rad));

        // Plot the point
        g.plot_point(x, y, R, G, B);
    }
}

int main(int argc, char** argv) {
    // 1. Setup the Plotter window (800x600 is standard)
    SDL_Plotter g(800, 600);

    // 2. Draw the starting circle (Red in the center)
    draw_circle(g, 400, 300, 100, 255, 0, 0);

    // 3. Main Loop: Keeps the window open and responsive
    while (!g.get<ctrl63>
