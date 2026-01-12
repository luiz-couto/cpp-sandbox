#include <print>
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>

inline long doSum(std::vector<long> &ones, std::vector<long> &index) {
    long sum = 0;
    for (long i = 0; i < index.size(); ++i) {
        sum += ones[index[i]];
    }
    return sum;
}

int main() {
    long N = 1000000;
    std::vector<long> index(N);

    for (long i = 0; i < index.size(); ++i) {
        index[i] = i;
    }

    std::vector<long> ones(N, 1);
    std::vector<long> shuffled = index;

    auto rng = std::default_random_engine {};
    std::ranges::shuffle(shuffled, rng);

    auto start = std::chrono::high_resolution_clock::now();
    
    long sum = doSum(ones, index);

    auto end = std::chrono::high_resolution_clock::now();
    std::print("Time: {} ms\n", std::chrono::duration<double, std::milli>(end - start).count());
    std::print("Result: {}", sum);

    return 0;
}