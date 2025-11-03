#include <iostream>
#include <chrono>
#include <memory>

// raw pointer
class stack {
	class node {
	public:
		int d;
		node* next = nullptr;
		node(int _d) : d(_d) {}
	};
	node* top;
public:
	stack() : top(nullptr) {}
	void push(int _d) {
		node* n = new node(_d);
		n->next = top;
		top = n;
	}
	void display() {
		std::cout << "T->";
		for (node* n = top; n != nullptr; n = n->next)
			std::cout << n->d << '|';
		std::cout << std::endl;
	}

	bool pop(int& d) {
		if (top == nullptr) return false;
		node* n = top;
		top = top->next;
		d = n->d;
		delete n;
		return true;

	}
};

// unique pointer
class stackUP {
	class node {
	public:
		int data;
		std::unique_ptr<node> next;
		node(int _d) : data(_d), next() {}
	};

	std::unique_ptr<node> top;
public:
	stackUP() : top() {}
	void push(int _d) {
		std::unique_ptr<node> n = std::make_unique<node>(_d);
		n->next = std::move(top);
		top = std::move(n);
	}
	bool pop(int& _d) {
		if (top == nullptr) return false;
		_d = top->data;
		top = std::move(top->next);
		return true;
	}
	void display() {
		std::cout << "T->";
		// need to use temp pointer
		for (node* tempPtr = top.get(); tempPtr != nullptr; tempPtr = tempPtr->next.get())
			std::cout << tempPtr->data << '|';
		std::cout << std::endl;
	}
};

// shared pointer
class stackSP {
	class node {
	public:
		int data;
		std::shared_ptr<node> next;
		node(int _d) : data(_d), next(nullptr) {}
	};
	std::shared_ptr<node> top;
public:
	stackSP() : top(nullptr) {}
	void push(int _d) {
		std::shared_ptr<node> n = std::make_shared<node>(_d);
		n->next = top;
		top = n;
	}
	bool pop(int& _d) {
		if (top == nullptr) return false;
		_d = top->data;
		top = top->next;
		return true;
	}
	void display() {
		std::cout << "T->";
	//	for (node* tempPtr = top.get(); tempPtr != nullptr; tempPtr = tempPtr->next.get())
		for (std::shared_ptr<node> tempPtr = top; tempPtr != nullptr; tempPtr = tempPtr->next)
			std::cout << tempPtr->data << '|';
		std::cout << std::endl;
	}
};

// I've removed the timing - please add yourself
template <typename Stack>
void run() {
    const auto start{std::chrono::steady_clock::now()};
	Stack s;
	unsigned int number = 1 << 22; 

	for (unsigned int i = 0; i < number; i++)
		s.push(i);

	int t;
	unsigned long long sum = 0;
	for (unsigned int i = 0; i < number; i++) {
		s.pop(t);
		sum += t; 
	}

    const auto finish{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{finish - start};

	std::cout << sum << std::endl; 
    std::cout << "Pushing and popping " << number << " took " << elapsed_seconds.count() << std::endl; 
}

int main() {
	run<stack>();
	run<stackUP>();
	run<stackSP>();
}
