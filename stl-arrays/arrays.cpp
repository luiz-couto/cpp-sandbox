#include <algorithm>
#include <array>
#include <random>
#include <print>

#define INTEGER_MAX_VALUE 10
#define SIZE 10

int generateRandomInteger() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, INTEGER_MAX_VALUE);

    return dist(mt);
}

int main() {
    std::array<int, SIZE> arr = {0};
    std::println("{}", arr);

    std::for_each(arr.begin(), arr.end(), [] (int &data) {
        data = generateRandomInteger();
    });

    std::println("{}", arr);
    return 0;
}