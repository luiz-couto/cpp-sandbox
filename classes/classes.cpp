#include <iostream>
#include <random>

#define INTEGER_MAX_VALUE 10
#define SIZE 10

int generateRandomInteger() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, INTEGER_MAX_VALUE);

    return dist(mt);
}

class MyAwesomeArray {
    private:
    int size;
    int *arr;

    public:
    MyAwesomeArray(int size) {
        this->size = size;
        this->arr = new int[size];
        for (int i=0; i<this->size; i++) {
            this->arr[i] = generateRandomInteger();
        }
    }

    void display() {
        for(int i=0; i<this->size; i++) {
            std::cout << this->arr[i] << "\t";
        }
        std::cout << std::endl;
    }

    int* getElementPtr(int index) {
        return &this->arr[index];
    }

    void reverseArray() {
        int* reversedArr = new int[this->size];
        for (int i=0; i<this->size; i++) {
            reversedArr[this->size-i-1] = this->arr[i];
        }
        this->arr = reversedArr;
        delete[] reversedArr;
    }
};

int main() {
    MyAwesomeArray* arr = new MyAwesomeArray(10);
    arr->display();
    arr->reverseArray();
    arr->display();
    return 0;
}