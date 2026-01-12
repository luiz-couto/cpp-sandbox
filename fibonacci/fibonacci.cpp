#include <print>
#include <iostream>
#include <chrono>

int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n;
    std::print("Input: ");
    std::cin >> n;

    auto start = std::chrono::high_resolution_clock::now();
    
    int sum = fibonacci(n);

    auto end = std::chrono::high_resolution_clock::now();
    std::print("Time: {}\n", std::chrono::duration<double, std::milli>(end - start).count());
    std::print("Result: {}", sum);
    return 0;
}