#include <iostream>

void helloWorld() {
    std::cout << "Hello World!" << std::endl;
};

void year() {
    int year;

    std::cout << "Which year it it?" << std::endl;
    std::cin >> year;

    std::cout << "The year is " << year << std::endl;
}

void greeting() {
    std::string name;

    std::cout << "What is your name?" << std::endl;
    std::cin >> name;

    std::cout << "Hello " << name << "!" << std::endl;
}

void integerOperationPrintResult(std::string text, int result) {
  std::cout << text << result << std::endl;
}

void integerOperations() {
    int a,b;

    std::cout << "Provide two integer numbers: " << std::endl;
    std::cin >> a;
    std::cin >> b;

    int sum = a + b;
    int difference = a - b;
    int product = a * b;
    int quotient = a / b;
    int remainder = a % b;

    integerOperationPrintResult("The sum is ", sum);
    integerOperationPrintResult("The difference is ", difference);
    integerOperationPrintResult("The product is ", product);
    integerOperationPrintResult("The quotient is ", quotient);
    integerOperationPrintResult("The remainder is ", remainder);
}

void floatOperationPrintResult(std::string text, float result) {
  std::cout << text << result << std::endl;
}

void floatOperations() {
    float a,b;

    std::cout << "Provide two float numbers: " << std::endl;
    std::cin >> a;
    std::cin >> b;

    float sum = a + b;
    float difference = a - b;
    float product = a * b;
    float quotient = a / b;
    float remainder = std::remainder(a, b);

    floatOperationPrintResult("The sum is ", sum);
    floatOperationPrintResult("The difference is ", difference);
    floatOperationPrintResult("The product is ", product);
    floatOperationPrintResult("The quotient is ", quotient);
    floatOperationPrintResult("The remainder is ", remainder);
}

void stringOperationPrintResult(std::string text, std::string result) {
  std::cout << text << result << std::endl;
}

void stringOperations() {
    std::string a,b;

    std::cout << "Provide two strings: " << std::endl;
    std::cin >> a;
    std::cin >> b;

    std::string sum = a + b;

    stringOperationPrintResult("The concatenation is ", sum);
}

void convertFarenheitToCelsius() {
    float farenheit;

    std::cout << "Farenheit input: ";
    std::cin >> farenheit;

    float celsius = (farenheit - 32) / 1.8;

    std::cout << "The temperature in Celsius is " << celsius << std::endl;
}

void convertPoundstToKilograms() {
    float pounds;

    std::cout << "Pounds input: ";
    std::cin >> pounds;

    float kilograms = pounds / 2.205;
    std::cout << "The weight in Kilograms is " << kilograms << std::endl;
}

int main() {
    convertPoundstToKilograms();
    return 0;
}