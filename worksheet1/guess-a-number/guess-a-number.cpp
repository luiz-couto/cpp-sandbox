#include <iostream>
#include <string>

#define MAX_NUMBER 1000

int generateRandomNumber() {
    srand (time(NULL));
    int random = rand();
    return random % MAX_NUMBER;
}

int main() {
    int randomNumber = generateRandomNumber();
    std::cout << "Guess the number: ";
    
    int userInput;
    int numberOfTries = 1;

    while(true) {
        std::cin >> userInput;
        if (userInput == randomNumber) {
            break;
        }

        std::string tip = " Go up!";
        if (userInput > randomNumber) {
            tip = " Go down!";
        }

        std::cout << "Incorrect!" << tip << " Guess again: ";
        numberOfTries++;
    }

    std::cout << "Correct!" << " Number of tries: " << std::to_string(numberOfTries) << std::endl;
    return 0;
}