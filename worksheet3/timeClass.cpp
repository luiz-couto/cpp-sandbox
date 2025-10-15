#include <iostream>

class sTime {
    public:
    int minutes;

    sTime(int hours, int minutes) {
        this->minutes = minutes + (60 * hours);
    }

    void display() {
        int hours = this->minutes / 60;
        int minutes = this->minutes % 60;
        std::cout << hours << ":" << minutes << std::endl;
    }

    void add(sTime &stime) {
        this->minutes = this->minutes + stime.minutes;
    }
};

int main() {
    sTime timeA = sTime(1, 30);
    sTime timeB = sTime(2, 45);
    timeA.add(timeB);
    timeA.display();
    return 0;
}
