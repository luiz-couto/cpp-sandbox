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
    int *arr = nullptr;

    public:
    MyAwesomeArray(int size) {
        this->size = size;
        this->arr = new int[size];
        for (int i=0; i<this->size; i++) {
            this->arr[i] = generateRandomInteger();
        }
    }

    MyAwesomeArray(MyAwesomeArray& A) {
        this->size = A.size;
        this->arr = new int[A.size];
        for (int i=0; i<this->size; i++) {
            this->arr[i] = A[i];
        }
    }

    ~MyAwesomeArray() {
        if (this->arr != NULL)
            delete[] this->arr;
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

    int& operator[](unsigned int index) {
        return this->arr[index];
    }

    MyAwesomeArray& operator = (MyAwesomeArray& A) {
        // FIGURE THIS OUT LATER!
        return *this;
    }

    friend std::ostream& operator << (std::ostream& stream, const MyAwesomeArray& Arr);

    void reverseArray() {
        int* reversedArr = new int[this->size];
        for (int i=0; i<this->size; i++) {
            reversedArr[this->size-i-1] = this->arr[i];
        }
        this->arr = reversedArr;
        delete[] reversedArr;
    }
};

std::ostream& operator << (std::ostream& stream, const MyAwesomeArray& Arr) {
    for(int i=0; i<Arr.size; i++) {
        stream << Arr.arr[i] << "\t";
    }
    stream << std::endl;
    return stream;
}

class MyAwesome2DArray {
    private:
    int size;
    int **arr;

    public:
    MyAwesome2DArray(int size) {
        this->size = size;
        this->arr = new int*[size];
        for (int i=0; i<this->size; i++) {
            this->arr[i] = new int[size];
        }
        for (int i=0; i<this->size; i++) {
            for (int j=0; j<this->size; j++) {
                this->arr[i][j] = generateRandomInteger();
            }
        }
    }

    ~MyAwesome2DArray() {
        for (int i=0; i<this->size; i++) {
            delete[] this->arr[i];
        }
        delete[] this->arr;
    }

    void display() {
        for (int i=0; i<this->size; i++) {
            for (int j=0; j<this->size; j++) {
                std::cout << this->arr[i][j] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

int main() {
    MyAwesomeArray A(10);
    A.display();

    MyAwesomeArray B(5);
    B.display();

    MyAwesomeArray C(A);
    C.display();

    // B = A;
    // B.display();

    std::cout << A << std::endl;
    return 0;
}