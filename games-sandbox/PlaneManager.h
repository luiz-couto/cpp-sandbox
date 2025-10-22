#pragma once
#include <random>
#include "iostream"
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
    float timeToNewPlane = 3.0f;

    public:
    PlaneManager(GamesEngineeringBase::Window *canvas, std::string planeImageFilename) {
        this->canvas = canvas;
        this->planeImageFilename = planeImageFilename;
        this->x = this->canvas->getWidth() / 2;
        this->y = -100;
    }

    void update(float dt) {
        this->timeElapsed += dt;

        if (currentSize < MAX_MANAGER_SIZE && this->timeElapsed > this->timeToNewPlane) {
            this->planes[currentSize] = new Plane(generateRandomNumber() % this->x, this->y, this->canvas, this->planeImageFilename);
            this->currentSize++;
            this->timeElapsed = 0;
            if (this->timeToNewPlane > 0.5) {
                this->timeToNewPlane = this->timeToNewPlane - 0.5;
            }
        }

        for (int i=0; i<currentSize; i++) {
            this->planes[i]->updateYPosition(3);
            // if (this->planes[i]->y > 768) {
            //     this->planes[i] = nullptr;
            //     this->currentSize--;
            // }
        }
    }

    void draw() {
        for (int i=0; i<currentSize; i++) {
            if (this->planes[i] != NULL) {
                this->planes[i]->draw();
            }
        }
    }
};