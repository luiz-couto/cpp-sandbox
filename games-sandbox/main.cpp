#include "GamesEngineeringBase.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

void drawImage(GamesEngineeringBase::Window* canvas, GamesEngineeringBase::Image *image, int positionX, int positionY) {
    for (int i=0; i < image->width; i++) {
        for (int j=0; j < image->height; j++) {
            if (image->alphaAt(i, j) > 0) {
                canvas->draw(i + positionX, j + positionY, image->at(i, j));
            }
        }
    }
}

int main() {
    // Create a canvas window with dimensions 1024x768 and title “Tiles"
    GamesEngineeringBase::Window canvas;
    canvas.create(1024, 768, "Tiles");
    bool running = true; // Variable to control the main loop's running state.

    GamesEngineeringBase::Image* image = new GamesEngineeringBase::Image();
    image->load("assets/L.png");

    while (running)
    {
    // Check for input (key presses or window events)


    // Clear the window for the next frame rendering
    canvas.clear();

    // Update game logic
    // Draw();
    drawImage(&canvas, image, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

    // Display the frame on the screen. This must be called once the frame
    //is finished in order to display the frame.
    canvas.present();
    }
    return 0;
}
