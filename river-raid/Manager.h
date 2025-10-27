#pragma once
#include "Plane.h"
#include "World.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

class Manager {
    private:
    GamesEngineeringBase::Window *canvas;
    Plane *hero;
    World *world;
    int worldIdx = 0;

    public:
    Manager(GamesEngineeringBase::Window *canvas) {
        this->canvas = canvas;

        int positionX = WINDOW_WIDTH / 2;
        int positionY = 645;
        this->hero = new Plane(positionX, positionY, this->canvas, "assets/L.png");

        this->world = new World(canvas);
    }

    void update() {
        this->worldIdx = this->worldIdx + 4;
        if (this->canvas->keyPressed('W')) {
            this->worldIdx = this->worldIdx + 8;
        }
        if (this->canvas->keyPressed('S')) {
            this->worldIdx = this->worldIdx - 3;
        }

        if (this->canvas->keyPressed('M')) {
            this->world->alphaOn = true;
        }
        if (this->canvas->keyPressed('N')) {
            this->world->alphaOn = false;
        }
        
        this->hero->reactToMovementKeys();
    }

    void draw() {
        this->world->draw(this->worldIdx);
        this->hero->draw();
    }

};