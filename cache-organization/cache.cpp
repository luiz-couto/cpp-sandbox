#include <print>
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

#define N 1000000

struct ParticleAoS {
    float x,y,z;
    float vx,vy,vz;
    float life;
    uint32_t pad; // to make it chunkier
};

struct ParticleSoA {
    std::vector<float> lifes;
    std::vector<float> xs;
    std::vector<float> ys;
    std::vector<float> zs;
    std::vector<float> vxs;
    std::vector<float> vys;
    std::vector<float> vzs;
    uint32_t pad; // to make it chunkier
};

float sumLifeAoS(std::vector<ParticleAoS> &p) {
    float sum = 0.0f;
    for (int i=0; i<p.size(); i++) {
        sum += p[i].life;
    }
    return sum;
}

float sumLifeSoA(ParticleSoA &p) {
    float sum = 0.0f;
    for (int i=0; i<p.lifes.size(); i++) {
        sum += p.lifes[i];
    }
    return sum;
}

float AoS() {
    std::vector<ParticleAoS> p(N);

    for (auto &e : p) e.life = 1.0f;

    float s = sumLifeAoS(p);
    return s;
}

float SoA() {
    ParticleSoA particleSoA;
    std::vector<float> lifes(N, 1.0f);

    particleSoA.lifes = lifes;
    float s = sumLifeSoA(particleSoA);
    return s;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    long long sum = AoS();

    auto end = std::chrono::high_resolution_clock::now();
    std::print("Time: {} ms\n", std::chrono::duration<double, std::milli>(end - start).count());
    std::print("Result: {}\n\n", sum);

    start = std::chrono::high_resolution_clock::now();

    long long sum2 = SoA();

    end = std::chrono::high_resolution_clock::now();
    std::print("Time: {} ms\n", std::chrono::duration<double, std::milli>(end - start).count());
    std::print("Result: {}", sum2);
}

