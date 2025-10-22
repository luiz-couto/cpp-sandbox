#include "GamesEngineeringBase.h"
#include "Plane.h"
#include "PlaneManager.h"

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
    
    GamesEngineeringBase::Timer tim = GamesEngineeringBase::Timer();

    int positionX = WINDOW_WIDTH / 2;
    int positionY = WINDOW_HEIGHT / 2;
    
    Plane *playerPlane = new Plane(positionX, positionY, &canvas, "assets/L.png");
    PlaneManager *planesManager = new PlaneManager(&canvas, playerPlane, "assets/L2.png");

    while (running)
    {
        // Check for input (key presses or window events)
        float dt = tim.dt();
        playerPlane->reactToMovementKeys();
        planesManager->update(dt);

        // Clear the window for the next frame rendering
        canvas.clear();

        // Update game logic
        // Draw();
        renderBackground(&canvas);
        playerPlane->draw();
        planesManager->draw();

        // Display the frame on the screen. This must be called once the frame
        //is finished in order to display the frame.
        canvas.present();
        //tim.reset();
    }
    return 0;
}
