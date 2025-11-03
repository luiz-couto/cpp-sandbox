#include <iostream>
#include <functional>
#include <stdexcept>

std::function<double(double, double)> getType(char operation) {
    switch (operation)
    {
    case '+':
        return [](double a, double b){ return a + b; };

    case '-':
        return [](double a, double b){ return a - b; };

    case '*':
        return [](double a, double b){ return a * b; };

    case '/':
        return [](double a, double b){ return a / b; };
    
    default:
        throw std::invalid_argument("received invalid operation");
    }
}

int main() {
    try {
        auto f = getType('+');
        std::cout << f(2,3) << std::endl;
    }
    catch (const std::invalid_argument& error) {
        std::cout << error.what() << std::endl;
    }

    return 0;
}