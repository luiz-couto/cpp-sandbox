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

class Node {
    public:
    std::shared_ptr<Node> next;
    int data;
    Node(int data) {
        this->data = data;
    }
};

class Stack {
    private:
    std::shared_ptr<Node> top;

    public:
    Stack() {
        this->top = nullptr;
    }

    void push(int data) {
        std::shared_ptr<Node> newNode = std::make_shared<Node>(Node(data));
        newNode->next = this->top;
        this->top = newNode;
    }
    
    bool pop(int *data) {
        if (this->top == nullptr) return false; 
        
        std::shared_ptr<Node> n = this->top;
        *data = n->data;
        this->top = n->next;

        return true;
    }

    void display() {
        for (std::shared_ptr<Node> n = top; n != nullptr; n = n->next) {
            std::cout << n->data << "\t";
        }
        std::cout << std::endl;
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