#include <iostream>

class Hero {
    public:
    virtual void sayName() = 0;
};

class Warrior : public Hero {
    public:
    void sayName() override {
        std::cout << "I am a Warrior!" << std::endl;
    }
};

class Mage : public Hero {
    public:
    void sayName() override {
        std::cout << "I am a Mage!" << std::endl;
    }
};


int main() {
    std::unique_ptr<Hero> hero;
    std::string selection;

    std::cout << "Choose your hero (mage/warrior): ";
    std::cin >> selection;

    if (selection == "mage") {
        hero = std::make_unique<Mage>(Mage());
    } else if (selection == "warrior") {
        hero = std::make_unique<Warrior>(Warrior());
    }
    
    hero->sayName();
    return 0;
}