#include <iostream>
#include <random>

struct vec {
    float x,y,z;
};

float generateRandomNumber() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0, 10);

    return dist(mt);
}

vec* createRandomVector() {
    float x = generateRandomNumber();
    float y = generateRandomNumber();
    float z = generateRandomNumber();

    vec* randomVector = new vec{x, y, z};
    return randomVector;
}

vec* sum(vec &vecA, vec &vecB) {    
    vec* resultVector = new vec{
        vecA.x + vecB.x,
        vecA.y + vecB.y,
        vecA.z + vecB.z
    };
    return resultVector;
}

void displayVector(vec &vecA) {
    std::cout << vecA.x << ", " << vecA.y << ", " << vecA.z << std::endl;
}

int main() {
    return 0;
}
