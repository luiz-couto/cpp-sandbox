#include <iostream>
#include <vector>

template <typename T>
class SimpleVector {
    T* data;
    std::size_t size;
    std::size_t capacity;

public:
    SimpleVector()
        : data(nullptr), size(0), capacity(0) {
    }

    SimpleVector(std::size_t cap)
        : data(new T[cap]), size(0), capacity(cap) {
    }

    ~SimpleVector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (size >= capacity) {
            // simple growth: double or go to 1
            std::size_t newCap = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[newCap];

            for (std::size_t i = 0; i < size; ++i)
                newData[i] = data[i];

            delete[] data;
            data = newData;
            capacity = newCap;
        }

        data[size++] = value;
    }

    std::size_t getSize() const { return size; }
    T& operator[](std::size_t i) { return data[i]; }

    void print() { // will required T to have cout overloaded 
        std::cout << "Capacity: " << capacity << "\t Size: " << size << " : ";
        for (unsigned int i = 0; i < size; i++)
            std::cout << data[i] << '\t';
        std::cout << std::endl;
    }

    // add copy and move constructors and assignment operators here
    SimpleVector(const SimpleVector& other)
        : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
        for (std::size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    SimpleVector& operator=(const SimpleVector& other) {
        if (this != &other) {
            delete[] data;

            data = new T[other.capacity];
            size = other.size;
            capacity = other.capacity;

            for (std::size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
};

int main() {
    SimpleVector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.print();

    // write some testing code here
    SimpleVector<int> b = a; // Test copy constructor
    b.print();

    SimpleVector<int> c;
    c = a; // Test copy assignment operator
    c.print();

    return 0;
}