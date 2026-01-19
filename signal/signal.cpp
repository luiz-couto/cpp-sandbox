#include <thread>
#include <vector>
#include <chrono>
#include <iostream>

class signal {
protected:
	float* sig;
	unsigned int size;

public:
	//signal() : signal(100000000) {}
	signal() : signal(1 << 27) {}
	signal(unsigned int _size) {
		size = _size;
		sig = new float[size];

		// randomise gamma
		for (unsigned int i = 0; i < size; i++) {
			sig[i] = (float)(rand() % 1000) / 1000.f;
		}
	}

	~signal() {
		delete[] sig;
	}

	void applyGamma(float gamma) {
		applyGammaSize(gamma, 0, size);
	}

	// this version does it from start to end - useful for the parallel part
	void applyGammaSize(float gamma, unsigned int start, unsigned int end) {
		for (unsigned int i = start; i < end; i++) {
			sig[i] = powf(sig[i], gamma);
		}
	}

	unsigned int getSize() { return size; }
};


class signalMT : public signal {
public:
	void applyGamma(float gamma, unsigned int procNum = 8)
	{
		// fill in MT version here
		std::vector<std::jthread> threads(procNum);

		unsigned int size = this->getSize();
		unsigned int chunkSize = size / procNum;

		for (int i = 0; i < threads.size(); i++) {
			unsigned int start = i * chunkSize;
			unsigned int end = (i == procNum - 1) ? size : (i + 1) * chunkSize;
			threads[i] = std::jthread(&signalMT::applyGammaSize, this, gamma, start, end);
		}
	}
};

int main() {
	signal s1;
	std::cout << "Signal size: " << s1.getSize() << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	s1.applyGamma(2.2f);
	auto end = std::chrono::high_resolution_clock::now();
	auto st = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Sequential: " << st << "ms" << std::endl;

	unsigned int procNum = std::thread::hardware_concurrency();
	std::cout << "Processor numbers = " << procNum << std::endl;
	signalMT sMT;
	start = std::chrono::high_resolution_clock::now();
	sMT.applyGamma(2.2f, procNum);
	end = std::chrono::high_resolution_clock::now();
	auto mt = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Parallel: " << procNum << ": " << mt << "ms" << std::endl;

	std::cout << "Speedup = " << static_cast<float>(st) / static_cast<float>(mt) << std::endl;
}
