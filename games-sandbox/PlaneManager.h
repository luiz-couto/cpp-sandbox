#pragma once
#include <random>
#include "Plane.h"
#include "GamesEngineeringBase.h"

#define MAX_MANAGER_SIZE 10

int generateRandomNumber() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 100000);

    return dist(mt);
}

class PlaneManager {
    private:
    GamesEngineeringBase::Window *canvas;
    std::string planeImageFilename;

    Plane *planes[MAX_MANAGER_SIZE];
    int currentSize = 0;
    float timeElapsed = 0;    

    int x,y;

    public:
    PlaneManager(GamesEngineeringBase::Window *canvas, std::string planeImageFilename) {
        this->canvas = canvas;
        this->planeImageFilename = planeImageFilename;
        this->x = this->canvas->getWidth() / 2;
        this->y = this->canvas->getHeight() / 2 + 200;
    }

    void update(float dt) {
        this->timeElapsed += dt;
        if (currentSize >= MAX_MANAGER_SIZE) return;

        if (this->timeElapsed > 3.0f) {
            this->planes[currentSize] = new Plane(generateRandomNumber() % this->x, this->y, this->canvas, this->planeImageFilename);
            this->currentSize++;
            this->timeElapsed = 0;
        }
    }

    void draw() {
        for (int i=0; i<currentSize; i++) {
            this->planes[i]->draw();
        }
    }
};