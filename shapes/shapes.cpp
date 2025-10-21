#include <iostream>

#define PI 3.14

class Shape {
    public:
    virtual float area() = 0;
    void displayArea() {
        std::cout << this->area() << std::endl;
    }
};

class Rectangle : public Shape {
    private:
    int width, height;
    
    public:
    Rectangle(int _width, int _height) : width(_width), height(_height) {}

    float area() {
        return this->width * this->height;
    }
};

class Circle : public Shape {
    private:
    int radius;

    public:
    Circle(int _radius) : radius(_radius) {}

    float area() {
        return PI * this->radius * this->radius;
    }
};

int main() {
    Circle* c = new Circle(3);
    Rectangle* r = new Rectangle(3, 2);

    Shape *shapeArr[2];
    shapeArr[0] = c;
    shapeArr[1] = r;

    for (int i=0; i<2; i++) {
        shapeArr[i]->displayArea();
    }

    return 0;
}