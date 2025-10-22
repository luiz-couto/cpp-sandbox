#include <iostream>

class Node {
    public:
    Node *next;
    int data;
    Node(int data) {
        this->data = data;
    }
};

class Stack {
    private:
    Node *top;

    public:
    Stack() {
        this->top = nullptr;
    }

    void push(int data) {
        Node *newNode = new Node(data);
        newNode->next = this->top;
        this->top = newNode;
    }
    
    bool pop(int *data) {
        if (this->top == nullptr) return false; 
        
        Node *n = this->top;
        *data = n->data;
        this->top = n->next;

        delete n;
        return true;
    }

    void display() {
        for (Node *n = top; n != nullptr; n = n->next) {
            std::cout << n->data << "\t";
        }
        std::cout << std::endl;
    }
};

int main() {
    Stack s;
    int poped;

    s.pop(&poped);

    s.push(10);
    s.push(12);
    s.push(13);
    s.display();

    s.pop(&poped);
    s.display();

    std::cout << poped << std::endl;

    return 0;
}