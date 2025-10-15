#include <iostream>
#include <random>
#include <cmath>

#define NUMBER_OF_QUESTIONS 3
#define INTEGER_MAX_VALUE 10

char POSSIBLE_OPERATIONS[6] = {'+', '-', '*', '/', '%', '^'};

int generateRandomInteger() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, INTEGER_MAX_VALUE);

    return dist(mt);
}

char generateRandomOperation() {
    int operationIdx = generateRandomInteger() % 6;
    return POSSIBLE_OPERATIONS[operationIdx];
}

int getAnswer(int x, int y, char operation) {
    switch (operation) {
    case '+':
        return x + y;
    case '-':
        return x - y;
    case '*':
        return x * y;
    case '/':
        return x / y;
    case '%':
        return x % y;
    case '^':
        return pow(x, y);
    default:
        return 0;
    }
}

int main() {
    int questionsRemaining = NUMBER_OF_QUESTIONS;
    int score = 0;

    while(questionsRemaining != 0) {
        int x = generateRandomInteger();
        int y = generateRandomInteger();
        char operation = generateRandomOperation();

        std::cout << x << " " << operation << " " << y << " ? ";

        int userInput;
        std::cin >> userInput;

        int answer = getAnswer(x, y, operation);
        if (userInput == answer) score ++;

        questionsRemaining--;
    }

    std::cout << "Final score: " << score << std::endl;
    return 0;
}