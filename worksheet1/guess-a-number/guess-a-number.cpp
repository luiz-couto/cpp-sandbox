#include <iostream>
#include <string>

#define MAX_NUMBER 10

int generateRandomNumber() {
    srand (time(NULL));
    int random = rand();
    return random % MAX_NUMBER;
}

int main() {
    int randomNumber = generateRandomNumber();
    std::cout << "Guess the number: ";
    
    int userInput;

    while(true) {
        std::cin >> userInput;
        if (userInput == randomNumber) {
            break;
        }
        std::cout << "Incorrect! Guess again: ";
    }

    std::cout << "Correct!" << std::endl;
    return 0;
}