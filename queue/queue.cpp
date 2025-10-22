#include <iostream>

class Node {
    public:
    Node *next;
    int data;
    Node(int data) {
        this->data = data;
    }
};

class Queue {
    private:
    Node *head;
    Node *tail;

    public:
    Queue() {
        this->head = nullptr;
        this->tail = nullptr;
    }

    void queue(int data) {
        Node *newNode = new Node(data);
        if (this->tail == nullptr) {
            this->head = newNode;
            this->tail = newNode;
            return;
        }

        newNode->next = nullptr;
        this->tail->next = newNode;
        this->tail = newNode;
    }
    
    bool dequeue(int *data) {
        if (this->head == nullptr) return false;

        Node *n = this->head;
        *data = n->data;

        this->head = this->head->next;
        if (this->head == nullptr) this->tail = nullptr;

        delete n;
        return true;
    }

    void display() {
        for (Node *n = this->head; n != nullptr; n = n->next) {
            std::cout << n->data << "\t";
        }
        std::cout << std::endl;
    }
};

int main() {
    Queue q;
    int deq;

    q.dequeue(&deq);

    q.queue(10);
    q.queue(11);
    q.queue(12);
    q.queue(13);
    q.display();

    q.dequeue(&deq);
    q.display();

    std::cout << deq << std::endl;

    return 0;
}