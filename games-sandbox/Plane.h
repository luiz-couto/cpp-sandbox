#pragma once

#include "GamesEngineeringBase.h"

#define VELOCITY 3

class Plane {
    private:
    GamesEngineeringBase::Image *image;
    GamesEngineeringBase::Window *canvas;
    
    public:
    int x,y;
    Plane(int x, int y, GamesEngineeringBase::Window *canvas, std::string filename) {
        this->x = x;
        this->y = y;

        this->canvas = canvas;

        this->image = new GamesEngineeringBase::Image();
        this->image->load(filename);
    }

    void draw() {
        for (int i=0; i < image->width; i++) {
            for (int j=0; j < image->height; j++) {
                if (image->alphaAt(i, j) > 0) {
                    if (j + this->y >= 0 && j + this->y < 768) {
                        canvas->draw(i + this->x, j + this->y, image->at(i, j));
                    }
                }
            }
        }
    }

    void updateYPosition(int y) {
        this->y = this->y + y;
    }

    void reactToMovementKeys() {
        if (this->canvas->keyPressed('W')) {
            this->y = max(this->y - VELOCITY, 0);
        }
        if (this->canvas->keyPressed('A')) {
            this->x = max(this->x - VELOCITY, 0);
        }
        if (this->canvas->keyPressed('D')) {
            this->x = min(this->x + VELOCITY, canvas->getWidth() - this->image->width);
        }
        if (this->canvas->keyPressed('S')) {
            this->y = min(this->y + VELOCITY, canvas->getHeight() - this->image->height);
        }
    }

};