#define _CRT_SECURE_NO_WARNINGS

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
#include <string>


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


int main()
{
    std::string inputPath = "resources/evening.jpg";
    //std::string inputPath = "resources/pexelsChristianHeitz.jpg";
    int width, height, channels;

    unsigned char* hImg = stbi_load(inputPath.c_str(), &width, &height, &channels, 3); // 3 forces 3 channels at the end

    if (!hImg) {
        std::cerr << "Failed to load image\n";
        return 0;
    }
    unsigned char* hOutImg = new unsigned char[width * height * channels];

    CPU(hImg, hOutImg, width, height, channels);
    stbi_write_jpg("resources/inverted.jpg", width, height, channels, hOutImg, 95);
    delete[] hOutImg;
    stbi_image_free(hImg);
    return 0;
}
