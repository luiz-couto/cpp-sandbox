#include <iostream>
#include <random>

int generateRandomNumber() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 100);

    return dist(mt);
}

int areaOfRectangle(int width, int height) {
    return width * height;
}

int calculateBMI(int weight, int height) {
    return weight / (height * height);
}

bool isEven(int value) {
    return value % 2 == 0;
}

void checkEvenOrOddForArray() {
    int arr[10] = {};
    for (int i=0; i<10; i++) {
        arr[i] = generateRandomNumber();
    }
    for (int i=0; i<10; i++) {
        std::cout << arr[i] << ": " << isEven(arr[i]) << "\t";
    }
}

int main() {
    checkEvenOrOddForArray();
    return 0;
}