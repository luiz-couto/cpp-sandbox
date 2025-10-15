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

int* generateRandomArray(int size) {
    int* arr = new int[size];
    for (int i=0; i<size; i++) {
        arr[i] = generateRandomNumber();
    }
    return arr;
}

void displayArray(int arr[], int size, std::string message) {
    std::cout << message << ": ";
    for (int i=0; i<size; i++) {
        std::cout << arr[i] << "\t";
    }
    std::cout << std::endl;
}

int* reverseIntegerArray(int arr[], int size) {
    int* reversedArr = new int[size];
    for (int i=0; i<size; i++) {
        reversedArr[i] = arr[size-i-1];
    }
    return reversedArr;
}

int findMaxArray(int arr[], int size) {
    int max = arr[0];
    for (int i=0; i<size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int* findMaxArrayAndIndex(int arr[], int size) {
    int max = arr[0];
    int index = 0;

    for (int i=0; i<size; i++) {
        if (arr[i] > max) {
            max = arr[i];
            index = i;
        }
    }

    int* result = new int[2];
    result[0] = index;
    result[1] = max;
    return result;
}

void shuffleArray(int arr[], int size) {
    for (int i=0; i<size; i++) {
        int randomIdx = generateRandomNumber() % size;
        std::swap(arr[i], arr[randomIdx]);
    }
}

void sortArray(int arr[], int size) {
    int dinamycSize = size;
    for (int i=0; i<size; i++) {
        int* idxAndMaxValue = findMaxArrayAndIndex(arr, dinamycSize);
        int maxIdx = idxAndMaxValue[0];
        std::swap(arr[maxIdx], arr[dinamycSize-1]);
        dinamycSize--;
    }
}

int main() {
    int size = 10;
    int* randomArr = generateRandomArray(size);
    displayArray(randomArr, size, "Random Arr");

    int* reversedArr = reverseIntegerArray(randomArr, size);
    displayArray(reversedArr, size, "Reversed");

    int max = findMaxArray(reversedArr, size);
    std::cout << "Max Value: " << max << std::endl;

    int* idxAndMaxValue = findMaxArrayAndIndex(reversedArr, size);
    std::cout << "Max Idx and Value: " << idxAndMaxValue[0] << ", " << idxAndMaxValue[1] << std::endl;

    sortArray(reversedArr, size);
    displayArray(reversedArr, size, "Sorted");

    shuffleArray(reversedArr, size);
    displayArray(reversedArr, size, "Shuffled");

    return 0;
}