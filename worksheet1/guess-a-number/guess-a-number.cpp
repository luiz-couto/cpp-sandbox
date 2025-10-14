#include <iostream>
#include <string>

#define MAX_NUMBER 1000

int generateRandomNumber() {
    srand (time(NULL));
    int random = rand();
    return random % MAX_NUMBER;
}

int getComputerGuess(int min, int max) {
    return (min + max) / 2;
}

int main() {
    int randomNumber = generateRandomNumber();
    std::cout << "Guess the number: ";
    
    int max = MAX_NUMBER;
    int min = 0;

    int computerGuess = getComputerGuess(min, max);
    int numberOfTries = 1;

    while(true) {
        std::cout << "Computer guess: " << std::to_string(computerGuess) << std::endl;
        if (computerGuess == randomNumber) {
            break;
        }
       
        if (computerGuess > randomNumber) {
            max = computerGuess;
        } else {
            min = computerGuess;
        }

        std::cout << "Incorrect!" << std::endl;
        numberOfTries++;
        computerGuess = getComputerGuess(min, max);
    }

    std::cout << "Correct!" << " Number of tries: " << std::to_string(numberOfTries) << std::endl;
    return 0;
}