#include <iostream>

int main() {
    int a = 42;
    int* p = &a; // Pointer to integer a

    std::cout << "Value of a: " << a << std::endl;
    std::cout << "Address of a: " << &a << std::endl;
    std::cout << "Value of p (address of a): " << p << std::endl;
    std::cout << "Value pointed to by p: " << *p << std::endl;

    *p = 100; // Modify the value of a through the pointer

    std::cout << "New value of a: " << a << std::endl;

    unsigned int size = 10;
    int* myAwesomeArr = new int[size];

    for(int i=0; i<size; i++) {
        myAwesomeArr[i] = i;
    }

    for(int i=0; i<size; i++) {
       std::cout << myAwesomeArr[i] << "\t";
    }

    int** anArrayOfPointers = new int* [size];
    for(int i=0; i<size; i++) {
        anArrayOfPointers[i] = new int[size];
    }

    

    delete[] myAwesomeArr;

    return 0;
}