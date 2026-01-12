#include <print>
#include <iostream>
#include <chrono>
#include <map>

std::map<int, int> fibMap;

int fibonacciWithMemory(int n) {
    if (fibMap.find(n) != fibMap.end()) {
        return fibMap[n];
    }
    if (n == 0) return 0;
    if (n == 1) return 1;

    int fib1 = fibonacciWithMemory(n - 1);
    int fib2 = fibonacciWithMemory(n - 2);
    fibMap[n - 1] = fib1;
    fibMap[n - 2] = fib2;

    fibMap[n] = fib1 + fib2;
    return fibMap[n];
}

int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    unsigned int n;
    std::print("Input: ");
    std::cin >> n;

    auto start = std::chrono::high_resolution_clock::now();
    
    int sum = fibonacci(n);

    auto end = std::chrono::high_resolution_clock::now();
    std::print("Time: {} ms\n", std::chrono::duration<double, std::milli>(end - start).count());
    std::print("Result: {}", sum);
    return 0;
}