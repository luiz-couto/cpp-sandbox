#include <vector>
#include <algorithm>
#include <print>
#include <iostream>

struct player{
    std::string name;
    int health;
    int power;
    int defense;
    int experience;
    void display() {
        std::cout << "Player: " << name
        << ", Health: " << health
        << ", Attack Power: " << power
        << ", Defense: " << defense
        << ", Experience: " << experience << "\n";
        std::cout << "-------------------------\n";
    }
};

int main() {
    std::vector<player> players = {
        {"Alice", 80, 50, 30, 1200},
        {"Bob", 100, 65, 25, 1500},
        {"Charlie", 50, 45, 35, 900},
        {"Diana", 20, 70, 40, 1800},
        {"Eve", 90, 55, 20, 1100}
    };

    // Display party
    // for (auto p : players) {
    //     p.display();
    // }

    // Find player with highest power
    auto maxPowerPlayer = (*players.begin());
    std::for_each(players.begin() + 1, players.end(), [&maxPowerPlayer](player p) {
        if ((maxPowerPlayer).power < p.power) maxPowerPlayer = p;
    });
    std::print("Max power player: ");
    (maxPowerPlayer).display();

    // //Find total health of party
    // //std::accumulate()

    // Increase experience of all
    for (auto &p : players) {
        p.experience+=10;
    };

    for (auto p : players) {
        p.display();
    }

    std::println("SORT BY DEFENSEEEE: ");
    // Sort by defense
    std::sort(players.begin(), players.end(), [](player &a, player &b) {
        return a.defense < b.defense;
    });

    for (auto p : players) {
        p.display();
    }

    // Return all players > 1500 exp in new vector
    // auto newPlayers = std::copy_if()


    return 0;
}