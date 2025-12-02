//=========================================
// C4C HOLIDAY PLOTTER STARTER CODE
// Challenge: Festive Console Art
//=========================================

#include <iostream>
#include <cmath> // For sin() and cos()
#include "SDL_Plotter.h"

using namespace std;

//---------------------------------------------------------
// Draw a basic circle using trigonometry
//---------------------------------------------------------
void draw_circle(SDL_Plotter& p, int centerX, int centerY, int radius, int R, int G, int B) {
    for (int angle = 0; angle < 360; angle += 1) {
        // Convert angle to radians
        double rad = angle * M_PI / 180.0;

        // Calculate (x, y) coordinates on the circle perimeter
        int x = (int)(centerX + radius * cos(rad));
        int y = (int)(centerY + radius * sin(rad));

        // Plot the point using the plotter object 'p'
        p.plot_point(x, y, R, G, B);
    }
}

int main(int argc, char** argv) {
    // 1. Setup the Plotter window (800x600 is standard)
    SDL_Plotter g(800, 600);

    // 2. Draw the starting circle (Red in the center)
    draw_circle(g, 400, 300, 100, 255, 0, 0);

    // 3. Important: Update the screen so the pixels actually appear!
    g.update();

    // 4. Main Loop: Keeps the window open and responsive
    // The loop continues as long as the user has NOT clicked the X button
    while (!g.get_quit()) {
        // Just wait
    }
    
    return 0;
}