#pragma once
#include "GamesEngineeringBase.h"

class Tile {
    private:
    GamesEngineeringBase::Window *canvas;
    GamesEngineeringBase::Image *tileImage;
    int y;

    public:
    Tile(GamesEngineeringBase::Window *canvas, std::string filename, int y) {
        this->canvas = canvas;
        this->y = y;
        GamesEngineeringBase::Image *tileImage = new GamesEngineeringBase::Image();
        tileImage->load(filename);
        this->tileImage = tileImage;
    }

    void draw() {
        for (int i=0; i < this->tileImage->width; i++) {
            for (int j=0; j < this->tileImage->height; j++) {
                if (this->tileImage->alphaAt(i, j) > 0) {
                    if (j + this->y >= 0 && j + this->y < 768) {
                        this->canvas->draw(i, j + this->y, this->tileImage->at(i, j));
                    }
                }
            }
        }
    }
};