// Barriers are used to sync inside the threads - so they continue from the same point

#include <iostream>
#include <thread>
#include <vector>
#include <barrier>
#include <print>

void helloThread(int id, std::barrier<> &bar) {
    for (int i=0; i<3; i++) {
        // some work
        std::print("Epoch {}\n", i);
        bar.arrive_and_wait();
    }
}

int main() {
    unsigned int numCPUs = std::jthread::hardware_concurrency();
    std::barrier bar(numCPUs);
    
    {
        std::vector<std::jthread> threads(numCPUs);
        for (int i=0; i<threads.size(); i++) {
            threads[i] = std::jthread(helloThread, i, std::ref(bar));
        }

    } // wait for jthreads to finish

    return 0;
}