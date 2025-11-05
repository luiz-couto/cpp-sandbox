#include <algorithm>
#include <ranges>
#include <random>
#include <print>
#include <vector>
#include <expected>

std::expected<float, std::string> squareRoot(float x) {
    if (x < 0) {
        return std::unexpected<std::string>("Square root of negative number");
    }
    return sqrt(x);
}

int main() {
    float num = -1;
    auto result = squareRoot(num);

    if (result) {
        std::println("The square root is {}", result.value());
        return 0;
    }

    std::println("Error! {}", result.error());
    return 0;
}