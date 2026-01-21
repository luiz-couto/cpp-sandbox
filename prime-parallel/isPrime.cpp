#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <chrono>
#include <print>

typedef std::chrono::high_resolution_clock Clock;

bool isPrime(unsigned long num) {
	if (num < 2) return false;           // 0 and 1 are not prime
	if (num == 2 || num == 3) return true; // 2 and 3 are prime
	if (num % 2 == 0) return false;      // Eliminate even numbers > 2

	// Check odd divisors up to sqrt(num)
	unsigned long limit = std::sqrt(num);
	for (unsigned long i = 3; i <= limit; i += 2) {
		if (num % i == 0) return false;
	}

	return true;
}

void doSequential(unsigned long endPrime) {
	unsigned int counter = 0;
	for (unsigned long i = 0; i < endPrime; i++)
		if (isPrime(i)) counter++;

	//std::cout << "Number of primes until " << endPrime << " is " << counter << std::endl; 
}

unsigned int doSequential(unsigned long startPrime, unsigned long endPrime) {
	unsigned int counter = 0;
	for (unsigned long i = startPrime; i < endPrime; i++)
		if (isPrime(i)) counter++;

	return counter;
}

void doParallel(unsigned long endPrime, unsigned int procNum) {
	std::vector<std::jthread> threads(procNum);
	std::vector<unsigned int> results(threads.size());

	unsigned long chunkSize = endPrime / procNum;

	for (int i=0; i<threads.size(); i++) {
		unsigned long start = i * chunkSize;
		unsigned long end = (i == procNum - 1) ? endPrime : (i + 1) * chunkSize;
		threads[i] = std::jthread([start, end, &results, i] {
			unsigned int counter = doSequential(start, end);
			results[i] = counter;
		});
	}

	for (int i=0; i<threads.size(); i++) {
		threads[i].join();
	}

	unsigned int counter = 0;
	for (int i=0; i<results.size(); i++) {
		counter += results[i];
	}

	//std::cout << "Number of primes until " << endPrime << " is " << counter << std::endl; 
}

int main() {
	unsigned long endPrime = 1 << 26;

	auto start = Clock::now();
	doSequential(endPrime);
	auto end = Clock::now();
	double duration = std::chrono::duration<double, std::milli>(end - start).count();
	std::print("{}	{}\n", "Seq", duration);
	
	//unsigned int procNum = std::thread::hardware_concurrency();
	unsigned int procNumList[6] = {1, 2, 4, 8, 16, 22};

	for (int i=0; i<6; i++) {
		start = Clock::now();
		doParallel(endPrime, procNumList[i]);
		end = Clock::now();
		duration = std::chrono::duration<double, std::milli>(end - start).count();
		std::print("{}	{}\n", procNumList[i], duration);
	}
}