#include "GamesEngineeringBase.h"
#include "Plane.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_NAME "C++ Sandbox!"

void renderBackground(GamesEngineeringBase::Window *canvas) {
    unsigned char backgroundColorPixel[3] = {100, 125, 255};
    for (int i=0; i<WINDOW_WIDTH; i++) {
        for (int j=0; j<WINDOW_HEIGHT; j++) {
            canvas->draw(i, j, backgroundColorPixel);
        }
    }
}

int main() {
    GamesEngineeringBase::Window canvas;
    canvas.create(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
    bool running = true;
    
    int positionX = WINDOW_WIDTH / 2;
    int positionY = WINDOW_HEIGHT / 2;
    
    Plane *plane = new Plane(positionX, positionY, &canvas, "assets/L.png");
    
    while (running)
    {
        // Check for input (key presses or window events)
        plane->reactToMovementKeys();

        // Clear the window for the next frame rendering
        canvas.clear();

        // Update game logic
        // Draw();
        renderBackground(&canvas);
        plane->draw();

        // Display the frame on the screen. This must be called once the frame
        //is finished in order to display the frame.
        canvas.present();
    }
    return 0;
}
