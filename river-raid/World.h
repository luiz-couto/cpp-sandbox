#pragma once
#include <iostream>
#include <random>
#include "TileSet.h"

#define WORLD_SIZE 10000
#define WINDOW_HEIGHT 768

int generateRandomNumber() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 100000);

    return dist(mt);
}

class World {
    private:
    GamesEngineeringBase::Window *canvas;
    TileSet *tileSet;
    int tilesIdxArr[WORLD_SIZE];

    public:
    World(GamesEngineeringBase::Window *canvas) {
        this->canvas = canvas;
        TileSet *tileset = new TileSet(canvas);
        this->tileSet = tileset;
        for (int i=0; i < WORLD_SIZE; i++) {
            this->tilesIdxArr[i] = generateRandomNumber() % 6;
        }
    }

    void draw(int idx) {
        // int idxTop = tilesIdxArr[idx];
        // int idxBottom = tilesIdxArr[idx+1];
        // this->tileSet->get(idxTop)->draw(0);
        
        int offset = idx % this->canvas->getHeight() / 2;
        this->tileSet->get(0)->draw(this->canvas->getHeight() / 2 + offset);
        this->tileSet->get(1)->draw(offset);
        this->tileSet->get(2)->draw(offset - (this->canvas->getHeight() / 2));
    }
};