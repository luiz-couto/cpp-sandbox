#pragma once
#include "GamesEngineeringBase.h"

class Tile {
    private:
    GamesEngineeringBase::Window *canvas;
    GamesEngineeringBase::Image *tileImage;

    public:
    Tile(GamesEngineeringBase::Window *canvas, std::string filename) {
        this->canvas = canvas;
        GamesEngineeringBase::Image *tileImage = new GamesEngineeringBase::Image();
        tileImage->load(filename);
        this->tileImage = tileImage;
    }

    void draw(int y) {
        for (int i=0; i < this->tileImage->width; i++) {
            for (int j=0; j < this->tileImage->height; j++) {
                if (this->tileImage->alphaAt(i, j) > 0) {
                    if (j + y >= 0 && j + y < 768) {
                        this->canvas->draw(i, j + y, this->tileImage->at(i, j));
                    }
                }
            }
        }
    }
};