#include <iostream>
#include <time.h>
#include <string>

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

void diceRoll() {
    srand (time(NULL));
    int random = rand();
    int roll = (random % 6) + 1;
    std::cout << "The dice roll was " << roll << std::endl;
}

void diceRollMultipleFaces() {
    int numberOfFaces;

    std::cout << "Number of faces: "; 
    std::cin >> numberOfFaces;

    srand (time(NULL));
    int random = rand();
    int roll = (random % numberOfFaces) + 1;

    std::cout << "The dice roll was " << roll << std::endl;
}

int uniqueDiceRoll() {
    srand (time(NULL));

    int random = rand();
    int roll = (random % 6) + 1;
    return roll;
}

void numberOfSevenDiceRolls() {
    int numberOfRounds = 10;
    int count = 0;

    for (int i=0; i<10; i++) {
        int firstRoll = uniqueDiceRoll();
        int secondRoll = uniqueDiceRoll();
        std::cout << firstRoll << " " << secondRoll << std::endl;
        if (firstRoll + secondRoll == 7) {
            count++;
        }
    }

    std::cout << "Number of 7 rolls: " << count;
}

void validateNameAndAge() {
    std::string name;
    int age;

    std::cout << "Name: ";
    std::cin >> name;

    std::cout << "Age: ";
    std::cin >> age;

    bool isAgeValid = age >= 2 && age <= 150;
    if (!isAgeValid) {
        std::cout << "Invalid age!" << std::endl;
        return;
    }

    std::cout << "Your name is " << name << " and you are " << age << " years old";
}

void simpleQuiz() {
    int score = 0;

    std::string firstQuestion = "Input any one of the following which is a capital city of a country:\n1. London\n2. Paris\n3. New York\n4. Coventry";
    std::cout << firstQuestion << std::endl;
    
    int firstAnswer;
    std::cin >> firstAnswer;

    if (firstAnswer == 1 || firstAnswer == 2) {
        score++;
    }

    std::string secondQuestion = "Name two countries which are in the EU:\n1. Norway\n2. Sweden\n3. Denwark\n4. France";
    std::cout << secondQuestion << std::endl;
    
    int secondAnswer1;
    std::cin >> secondAnswer1;

    int secondAnswer2;
    std::cin >> secondAnswer2;

    if (!(secondAnswer1 == 1 || secondAnswer2 == 1)) {
        score++;
    }

    std::cout << "Score: " << score << std::endl;
}

void powerFromZeroToTwentyFive() {
    for(int i=0; i<=25; i++) {
        int square = i*i;
        int fourthPower = square * square;
        std::cout << "Square of " << i << ": " << square << " | 4th power: " << fourthPower << std::endl;
    }
}

void validateNameAndAgeAskAgain() {
    std::string name;
    int age;

    std::cout << "Name: ";
    std::cin >> name;

    while(true) {
        std::cout << "Age: ";
        std::cin >> age;

        bool isAgeValid = age >= 2 && age <= 150;
        if (isAgeValid) {
            break;
        }
        std::cout << "Invalid age!" << std::endl;
    }

    std::cout << "Your name is " << name << " and you are " << age << " years old";
}

#define ARR_SIZE 10

void randomIntegersArray() {
    int integers[ARR_SIZE] = {};
    for (int i=0; i<ARR_SIZE; i++) {
        srand (time(0) + i * 10);
        int number = (rand() % 999);
        integers[i] = number;
    }

    for (int i=0; i<ARR_SIZE; i++) {
        std::cout << integers[i] << "\t";
    }

    std::cout << std::endl;
}

std::string getMonthStringSwitch(int monthNum) {
    switch (monthNum) {
        case 1:
            return "January";
        case 2:
            return "February";
        case 3:
            return "March";
        case 4:
            return "April";
        case 5:
            return "May";
        case 6:
            return "June";
        case 7:
            return "July";
        case 8:
            return "August";
        case 9:
            return "September";
        case 10:
            return "October";
        case 11:
            return "November";
        case 12:
            return "December";
        default:
            return "Try Again";
    }
}

std::string getMonthStringArray(int monthNum) {
    std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    return (monthNum >= 1 && monthNum <= 12) ? months[monthNum - 1] : "Try Again";
}

void formatDate() {
    int day,month;
    std::string monthString;

    while(true) {
        std::cout << "Enter day: ";
        std::cin >> day;

        if (day < 1 || day > 31) {
            continue;
        }

        std::cout << "Enter month: ";
        std::cin >> month;

        //monthString = getMonthStringSwitch(month);
        monthString = getMonthStringArray(month);
        if (monthString != "Try Again") {
            break;
        }
    }

    std::string formattedDate = std::to_string(day) + "th " + monthString;
    std::cout << "Formatted date: " << formattedDate << std::endl;
}

int main() {
    formatDate();
    return 0;
}