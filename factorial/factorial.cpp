#include <print>
#include <iostream>
#include <chrono>
#include <vector>

std::vector<long long> factorialTable;

long long factorialMemo(int n) {
    if (n >= factorialTable.size()) {
        factorialTable.resize(n + 1, -1);
    }

    if (factorialTable[n] != -1) {
        return factorialTable[n];
    }

    long long fac = n * factorialMemo(n - 1);
    factorialTable[n] = fac;

    return factorialTable[n];
}

int main() {
    unsigned int n;
    std::print("Input: ");
    std::cin >> n;

    auto start = std::chrono::high_resolution_clock::now();
    
    factorialTable.resize(2, -1);
    factorialTable[0] = 1;
    factorialTable[1] = 1;

    long long sum = factorialMemo(n);

    auto end = std::chrono::high_resolution_clock::now();
    std::print("Time: {} ms\n", std::chrono::duration<double, std::milli>(end - start).count());
    std::print("Result: {}", sum);
    return 0;
}