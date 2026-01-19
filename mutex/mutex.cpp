#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <format>
#include <print>

class Wallet {
    int balance = 0;
    std::mutex mtx;
public:

    void addMoney(int amount) {
        std::lock_guard<std::mutex> guard(mtx);
        if (amount < 0) return;
        balance += amount;
    }

    int getBalance() {
        return balance;
    }
};

int main() {
    int numThreads = 20;
    Wallet myWallet;

    {
        std::vector<std::jthread> threads;
        threads.reserve(numThreads);

        // Simulate numThreads people putting 100 into the same wallet concurrently
        for (int i=0; i<numThreads; i++) {
            threads.emplace_back(std::jthread(&Wallet::addMoney, &myWallet, 100));
        }

    } // waiting for jthreads to finish (they work by context)

    std::print("Final Balance: {}\n", myWallet.getBalance());
}