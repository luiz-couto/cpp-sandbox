#pragma once
#include <iostream>
#include <random>
#include "TileSet.h"

#define WORLD_SIZE 10000
#define WINDOW_WIDTH 1024
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
    TileSet *alphas;
    int tilesIdxArr[WORLD_SIZE];
    
    public:
    bool alphaOn = false;
    World(GamesEngineeringBase::Window *canvas) {
        this->canvas = canvas;
        TileSet *tileset = new TileSet(canvas, false);
        this->tileSet = tileset;
        for (int i=0; i < WORLD_SIZE; i++) {
            this->tilesIdxArr[i] = generateRandomNumber() % 6;
        }

        TileSet *alphas = new TileSet(canvas, true);
        this->alphas = alphas;
    }

    void collision(int idx, int yHero) {
        int tileHeight = 384;
        int Y = idx / 384;
        int offset = idx % 384;
        int lineYPos = (tileHeight * 2) - yHero / 2;
        int tileIdx = this->tilesIdxArr[(Y) % WORLD_SIZE];

        unsigned int yCoord = tileHeight - ((yHero + idx) % tileHeight);

        for (int i=0; i<WINDOW_WIDTH; i++) {
            Tile *alphaTile = this->alphas->get(tileIdx);
            GamesEngineeringBase::Image *tileImage = alphaTile->tileImage;

            if (tileImage->at(i, yCoord, 0) == 0) {
                this->canvas->draw(i, lineYPos, 255, 0, 0);
            } else {
                this->canvas->draw(i, lineYPos, 0, 255, 0);
            }
        }
    }

    void draw(int idx) {
        int offset = idx % 384;
        int Y = idx / 384;

        TileSet *selectedTiles = this->tileSet;
        if (this->alphaOn) {
            selectedTiles = this->alphas;
        }
        selectedTiles->get(this->tilesIdxArr[Y % WORLD_SIZE])->draw(this->canvas->getHeight() / 2 + offset);
        selectedTiles->get(this->tilesIdxArr[(Y + 1) % WORLD_SIZE])->draw(offset);
        selectedTiles->get(this->tilesIdxArr[(Y + 2) % WORLD_SIZE])->draw(offset - (this->canvas->getHeight() / 2));

        //this->collision(Y, offset);
    }
};