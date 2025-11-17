#include <print>

#define DEFAULT_MAX_SIZE 100

template<typename T, int MAX_SIZE = DEFAULT_MAX_SIZE>
class PDList {
    private:
    T* list[MAX_SIZE];
    int nextFreeIdx = 0;
    int iteratorIdx = 0;
    bool isIterating = false;

    public:
    PDList() {
        for (int i=0; i<MAX_SIZE; i++) {
            list[i] = nullptr;
        }
    }

    void add(T *item) {
        list[nextFreeIdx] = item;
        nextFreeIdx++;
    }
    
    void deleteByIdx(int idx) {
        delete list[idx];
        list[idx] = nullptr;
        for (int i = idx + 1; i <= nextFreeIdx; i++) {
            list[i - 1] = list[i];
        }
        nextFreeIdx--;

        if (isIterating) {
            iteratorIdx--;
        }
    }

    void display(bool showNulls = true) {
        for (int i = 0; i < MAX_SIZE; i++) {
            if (list[i] != nullptr) {
                std::print("{} ", *(list[i]));
                continue;
            }
            if (showNulls) {
                std::print("nullptr ");
            }
        }
        std::println();
    }

    template<typename Func>
    void forEach(Func func) {
        isIterating = true;
        for (iteratorIdx = 0; iteratorIdx < nextFreeIdx; iteratorIdx++) {
            func(*list[iteratorIdx], iteratorIdx);
        }
        isIterating = false;
    }

    ~PDList() {
        for (int i = 0; i < nextFreeIdx; i++) {
            delete list[i];
        }
    }
};

int main() {
    PDList<int, 11> pdlist;

    for (int i = 0; i < 10; i++) {
        int *num = new int(i * 10);
        pdlist.add(num);
    }

    pdlist.display();
    pdlist.deleteByIdx(5);
    pdlist.add(new int(999));
    pdlist.deleteByIdx(0);
    pdlist.deleteByIdx(3);

    pdlist.display();

    pdlist.forEach([&pdlist](int &item, int idx){
        if (item == 70) {
            pdlist.deleteByIdx(idx);
        }
    });

    pdlist.display();

    return 0;
}