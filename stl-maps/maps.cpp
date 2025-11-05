#include <algorithm>
#include <map>
#include <random>
#include <print>

class Inventory {
    private:
    std::map<std::string, int> inventory;

    public:
    Inventory() {}

    void addItem(std::string item, int number) {
        this->inventory[item] = number;
    }

    void display() {
        println("{}", this->inventory);
    }

    void useItem(std::string item) {
        this->inventory[item] -= 1;
    }
};

int main() {
    Inventory inv;

    inv.addItem("health potion", 3);
    inv.addItem("attack potion", 2);
    inv.addItem("armour", 1);

    inv.display();

    inv.useItem("health potion");
    inv.display();
    
    return 0;
}