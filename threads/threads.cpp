#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <format>

void helloThread(int id) {
    std::string threadID = std::format("{}", std::this_thread::get_id());
    std::string message = "Hello world! I am thread " + std::to_string(id) + " ; my id is " + threadID + "\n";
    std::cout << message;
}

int main() {
    // get number of CPUs – these include hyperthreaded
    unsigned int numCPUs = std::thread::hardware_concurrency();
    std::cout << "Number of CPUs is " << numCPUs << std::endl;

    std::vector<std::thread> threads(numCPUs);

    // launch threads
    for (int i = 0; i < threads.size(); i++)
        threads[i] = std::thread([&i] { 
            std::string threadID = std::format("{}", std::this_thread::get_id());
            std::string message = "Hello world! I am thread " + std::to_string(i) + " ; my id is " + threadID + "\n";
            std::cout << message;
        });

    // wait for threads to finish
    for (auto& t : threads)
        t.join();
    
    return 0;
}