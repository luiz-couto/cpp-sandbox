#include <iostream>

class MyStruct {
    public:
    int data;

    friend std::ostream& operator << (std::ostream& stream, const MyStruct& a);
};

std::ostream& operator << (std::ostream& stream, const MyStruct& a) {
    stream << a.data;
    return stream;
}

template <typename T>
void swp(T &a, T &b) {
    T aux = a;
    a = b;
    b = aux;
}

template <typename T>
T mx(T a, T b) {
    if (a > b) {
        return a;
    }
    return b;
}

template <>
std::string mx<std::string>(std::string a, std::string b) {
    if (a.length() > b.length()) {
        return a;
    }
    return b;
}

template <typename T>
class Node {
    public:
    Node *next;
    T data;
    Node(T data) {
        this->data = data;
    }
};

template <typename T>
class Stack {
    private:
    Node<T> *top;

    public:
    Stack() {
        this->top = nullptr;
    }

    void push(T data) {
        Node<T> *newNode = new Node<T>(data);
        newNode->next = this->top;
        this->top = newNode;
    }
    
    bool pop(T *data) {
        if (this->top == nullptr) return false; 
        
        Node<T> *n = this->top;
        *data = n->data;
        this->top = n->next;

        delete n;
        return true;
    }

    void display() {
        for (Node<T> *n = top; n != nullptr; n = n->next) {
            std::cout << n->data << "\t";
        }
        std::cout << std::endl;
    }
};

template <typename T, int SIZE = 10>
class GrowableArray {
    private:
    T *arr;
    int maxSize = SIZE;
    int size = 0;

    public:
    GrowableArray() {
        this->arr = new T[maxSize];
    }

    ~GrowableArray() {
        delete[] arr;
    }

    void add(T item) {
        if (size < maxSize) {
			this->arr[size++] = item;
            return;
        }

        T* newarray;
        this->maxSize *= 2;
        std::cout << "Growing array to " << maxSize << std::endl;

        newarray = new T[maxSize]; // should check if there was enough space really
        memcpy(newarray, this->arr, size * sizeof(T));
        delete[] this->arr;
        this->arr = newarray;
        this->arr[size++] = item;
    }
    
    void display() {
		for (int i = 0; i < size; i++)
			std::cout << this->arr[i] << '\t';
		std::cout << std::endl;
	}

	T& operator[] (unsigned int index) {
		// lazy implementation should test bounds really 
		return this->arr[index];
	}

};

int main() {
    MyStruct a;
    a.data = 2;

    MyStruct b;
    b.data = 3;

    std::cout << "a.data: " << a.data << std::endl;
    std::cout << "b.data: " << b.data << std::endl;

    swp<MyStruct>(a, b);

    std::cout << "a.data: " << a.data << std::endl;
    std::cout << "b.data: " << b.data << std::endl;

    Stack<int> s;
    int poped;
    s.pop(&poped);
    s.push(10);
    s.push(12);
    s.push(13);
    s.display();

    Stack<std::string> strStack;
    std::string strPoped;
    strStack.pop(&strPoped);
    strStack.push("Hello");
    strStack.push("World!");
    strStack.push("C++ Templates!");
    strStack.pop(&strPoped);
    strStack.display();

    Stack<MyStruct> structStack;
    MyStruct structPoped;
    structStack.pop(&structPoped);
    structStack.push(a);
    structStack.push(b);
    structStack.display();

    return 0;
}