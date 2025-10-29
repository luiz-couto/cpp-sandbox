#pragma once

#include "GamesEngineeringBase.h"

#define VELOCITY 6

class Plane {
    private:
    GamesEngineeringBase::Image *image;
    GamesEngineeringBase::Window *canvas;
    
    public:
    int yCollide;
    int x,y;
    Plane(int x, int y, GamesEngineeringBase::Window *canvas, std::string filename) {
        this->x = x;
        this->y = y;

        this->canvas = canvas;

        this->image = new GamesEngineeringBase::Image();
        this->image->load(filename);

        this->yCollide = (this->image->height / 3) * 2;
    }

    void draw() {
        for (int i=0; i < image->width; i++) {
            for (int j=0; j < image->height; j++) {
                if (image->alphaAt(i, j) > 0) {
                    if (j + this->y >= 0 && j + this->y < 768) {
                        this->canvas->draw(i + this->x, j + this->y, image->at(i, j));
                    }
                }
            }
        }
    }

    void drawCollisionLine() {
        int centerY = this->y + this->yCollide;
        int lineThickness = 1;
        for (int t=0; t < lineThickness; t++) {
            for (int i=0; i < this->image->width; i++) {
                this->canvas->draw(i + this->x, centerY + t, 0, 255, 0);
            }
        }
    }

    void updateYPosition(int y) {
        this->y = this->y + y;
    }

    bool checkColision(Plane *anotherPlane) {
        float radius = this->image->height / 2;
        float distanceBetweenCenters = sqrt(pow(this->x - anotherPlane->x, 2) +  pow(this->y - anotherPlane->y, 2));
        float distance = max(0, distanceBetweenCenters - 2 * radius);
        if (distance == 0) {
            return true;
        }
        return false;
    }

    void reactToMovementKeys() {
        if (this->canvas->keyPressed('A')) {
            this->x = max(this->x - VELOCITY, 0);
        }
        if (this->canvas->keyPressed('D')) {
            this->x = min(this->x + VELOCITY, canvas->getWidth() - this->image->width);
        }
    }

};