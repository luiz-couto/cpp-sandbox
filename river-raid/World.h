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
        int offset = idx % 384;
        int Y = idx / 384;

        this->tileSet->get(this->tilesIdxArr[Y % WORLD_SIZE])->draw(this->canvas->getHeight() / 2 + offset);
        this->tileSet->get(this->tilesIdxArr[(Y + 1) % WORLD_SIZE])->draw(offset);
        this->tileSet->get(this->tilesIdxArr[(Y + 2) % WORLD_SIZE])->draw(offset - (this->canvas->getHeight() / 2));
    }
};