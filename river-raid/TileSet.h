#pragma once
#include <string>
#include "Tile.h"

#define SIZE 6

class TileSet {
    private:
    GamesEngineeringBase::Window *canvas;
    Tile *tiles[SIZE];

    public:
    TileSet(GamesEngineeringBase::Window *canvas) {
        this->canvas = canvas;
        for (int i=0; i<SIZE; i++) {
            this->tiles[i] = new Tile(this->canvas, "assets/" + std::to_string(i) + ".png");
        }
    }

    Tile* get(int idx) {
        return this->tiles[idx];
    }
};