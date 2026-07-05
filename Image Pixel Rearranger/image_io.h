#pragma once
#include <vector>
#include <string>
#include <cstdint>

struct Pixel {
    uint8_t r, g, b;
};

struct Image {
    int width;
    int height;
    std::vector<Pixel> pixels;
};

// Loads an image from filename
Image loadImage(const std::string& filename);

// Saves an image to filename
void saveImage(const std::string& filename, const Image& img);