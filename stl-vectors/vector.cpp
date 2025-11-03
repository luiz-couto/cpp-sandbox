#include <vector>
#include <print>

int main() {
    std::vector<float> vec = {0, 1, 2, 3};

    for (float &n : vec) {
        n++;
    }

    for (float n : vec) {
        std::print("{} - ", n);
    }
}