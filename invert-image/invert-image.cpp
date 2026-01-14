#define _CRT_SECURE_NO_WARNINGS

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
#include <string>
#include <chrono>


void CPU(const unsigned char* hImg, unsigned char* hOutImg, int width, int height, int channels) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < channels; c++) {
                int idx = (((y * width) + x) * channels);
                hOutImg[idx + c] = 255 - hImg[idx + c];
            }
        }
    }
}

void GPU(const unsigned char* hImg, unsigned char* hOutImg, int width, int height, int channels) {
    const __m256i v255 = _mm256_set1_epi8(static_cast<char>(255));
    size_t totalPixels = static_cast<size_t>(width) * height * channels;
    size_t i = 0;

    // Process 32 bytes at a time while we have enough data
    for (; i + 32 <= totalPixels; i += 32) {
        __m256i v = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(hImg + i));
        __m256i out = _mm256_subs_epu8(v255, v);
        _mm256_storeu_si256(reinterpret_cast<__m256i*>(hOutImg + i), out);
    }

    // Handle remaining bytes
    for (; i < totalPixels; i++) {
        hOutImg[i] = 255 - hImg[i];
    }
}


int main()
{
    std::string inputPath = "resources/evening.jpg";
    //std::string inputPath = "resources/pexelsChristianHeitz.jpg";
    int width, height, channels;

    unsigned char* hImg = stbi_load(inputPath.c_str(), &width, &height, &channels, 3); // 3 forces 3 channels at the end
    channels = 3; // Set channels to 3 since we forced it in stbi_load

    if (!hImg) {
        std::cerr << "Failed to load image\n";
        return 0;
    }
    unsigned char* hOutImg = new unsigned char[width * height * channels];

    auto start = std::chrono::high_resolution_clock::now();
    GPU(hImg, hOutImg, width, height, channels);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    stbi_write_jpg("resources/inverted2.jpg", width, height, channels, hOutImg, 95);
    delete[] hOutImg;
    stbi_image_free(hImg);
    return 0;
}
