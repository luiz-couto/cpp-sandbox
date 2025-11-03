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

    std::print("{}", vec);

    for (auto i = vec.begin(); i < vec.end(); i++) {
        std::print("{} - ", *i);
    }

    std::println("");
    vec.erase(vec.begin() + 1);
    std::print("{}", vec);
    return 0;
}