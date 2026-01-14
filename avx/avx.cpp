#include <immintrin.h>
#include <print>
#include <chrono>

void testSupport() {
    int cpu_info[4];
    __cpuid(cpu_info, 7);

    bool avx512_supported = (cpu_info[1] & (1 << 16)) != 0;
    bool avx2_supported = (cpu_info[1] & (1 << 5)) != 0;

    std::print("AVX-512 supported: {}\n", avx512_supported ? "Yes" : "No");
    std::print("AVX2 supported: {}\n", avx2_supported ? "Yes" : "No");
}

void add_avx2(float* a, float* b, float* result) {
    // load 8 floats from each array
    __m256 va = _mm256_load_ps(a);
    __m256 vb = _mm256_load_ps(b);

    __m256 vc = _mm256_add_ps(va, vb);
    _mm256_store_ps(result, vc);
}

void testAVX2() {
    alignas(64) float a[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    alignas(64) float b[8] = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f};
    alignas(64) float result[8];

    add_avx2(a, b, result);

    std::print("Result of AVX2 addition:\n");
    for (int i = 0; i < 8; ++i) {
        std::print("{} ", result[i]);
    }
    std::print("\n");
}

void multiply_avx2_8(float* a, float* b, float* result) {
    // load 8 floats from each array
    __m256 va = _mm256_load_ps(a);
    __m256 vb = _mm256_load_ps(b);

    __m256 vc = _mm256_mul_ps(va, vb);
    _mm256_store_ps(result, vc);
}

void multiplyLargeArrays(float* a, float* b, float* result, size_t size) {
    for (size_t i = 0; i < size; i += 8) {
        multiply_avx2_8(&a[i], &b[i], &result[i]);
    }

    // handle remaining elements if size is not multiple of 8
    for (size_t i = size - (size % 8); i < size; ++i) {
        result[i] = a[i] * b[i];
    }
}

void dotProduct_avx2(float* a, float* b, float* result, size_t size) {
    __m256 sum = _mm256_setzero_ps();

    for (size_t i = 0; i < size; i += 8) {
        __m256 va = _mm256_load_ps(&a[i]);
        __m256 vb = _mm256_load_ps(&b[i]);
        __m256 prod = _mm256_mul_ps(va, vb);
        sum = _mm256_add_ps(sum, prod);
    }

    // Horizontal add to get the final sum
    float temp[8];
    _mm256_store_ps(temp, sum);
    *result = temp[0] + temp[1] + temp[2] + temp[3] + temp[4] + temp[5] + temp[6] + temp[7];

    // handle remaining elements if size is not multiple of 8
    for (size_t i = size - (size % 8); i < size; ++i) {
        *result += a[i] * b[i];
    }
}

void testAVX2Multiplication() {
    const size_t size = 16;
    alignas(64) float a[size] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
    alignas(64) float b[size] = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f, 90.0f, 100.0f, 110.0f, 120.0f, 130.0f, 140.0f, 150.0f, 160.0f};
    alignas(64) float result[size];

    multiplyLargeArrays(a, b, result, size);

    std::print("Result of AVX2 multiplication:\n");
    for (int i = 0; i < size; ++i) {
        std::print("{} ", result[i]);
    }
    std::print("\n");
}

void add_avx2_doubles(double* a, double* b, double* result) {
    // load 4 doubles from each array
    __m256d va = _mm256_load_pd(a);
    __m256d vb = _mm256_load_pd(b);

    __m256d vc = _mm256_add_pd(va, vb);
    _mm256_store_pd(result, vc);
}

void testAVX2Doubles() {
    alignas(64) double a[4] = {1.0, 2.0, 3.0, 4.0};
    alignas(64) double b[4] = {10.0, 20.0, 30.0, 40.0};
    alignas(64) double result[4];

    add_avx2_doubles(a, b, result);

    std::print("Result of AVX2 double addition:\n");
    for (int i = 0; i < 4; ++i) {
        std::print("{} ", result[i]);
    }
    std::print("\n");
}

int main() {
    //testSupport();
    //testAVX2Doubles();
    //testAVX2();

    auto start = std::chrono::high_resolution_clock::now();
    testAVX2Multiplication();
    auto end = std::chrono::high_resolution_clock::now();
    std::print("Time: {} ms\n", std::chrono::duration<double, std::milli>(end - start).count());

    return 0;
}