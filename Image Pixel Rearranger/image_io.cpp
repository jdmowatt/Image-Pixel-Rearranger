#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

#include "image_io.h"
#include <iostream>

Image loadImage(const std::string& filename) {
    // Declare output variables and run stbi_load
    int width, height, channels;
    unsigned char* buffer = stbi_load(filename.c_str(), &width, &height, &channels, 3);

    // Validate
    if (!buffer) {
        std::cout << "Error loading image " << filename << std::endl;
        exit(1);
    }

    // Parse Buffer
    std::vector<Pixel> loadedPixels;
    for (int i = 0; i < width * height; i++) {
        loadedPixels.push_back(Pixel{buffer[i*3], buffer[i*3+1], buffer[i*3+2]});
    }

    // Create output Image struct
    Image loadedImage = { width, height, loadedPixels };

    // Free buffer memory
    stbi_image_free(buffer);

    return loadedImage;
}

void saveImage(const std::string& filename, const Image& img) {
    // Initialize Variables
    int width = img.width;
    int height = img.height;
    std::vector<unsigned char> buffer(width * height * 3);

    // Load Pixels into Buffer
    for (int i = 0; i < width * height; i++) {
        buffer[i*3] = img.pixels[i].r;
        buffer[i*3+1] = img.pixels[i].g;
        buffer[i*3+2] = img.pixels[i].b;
    }

    // Write image to filename
    int result = stbi_write_png(filename.c_str(), width, height, 3, buffer.data(), 0);
    if (!result) {
        std::cout << "Error saving image " << filename << std::endl;
    } else {
        std::cout << "Saved image to " << filename << std::endl;
    }
}

Image resizeImage(const Image& img, int newWidth, int newHeight) {
    std::cout << "Resizing ...\n";

    // Initialize Variables
    int width = img.width;
    int height = img.height;
    std::vector<unsigned char> inputBuffer(width * height * 3);
    std::vector<unsigned char> outputBuffer(newWidth * newHeight * 3);


    // Load Pixels into Input Buffer
    for (int i = 0; i < width * height; i++) {
        inputBuffer[i*3] = img.pixels[i].r;
        inputBuffer[i*3+1] = img.pixels[i].g;
        inputBuffer[i*3+2] = img.pixels[i].b;
    }

    // Resize Image
    stbir_resize_uint8_srgb(
        inputBuffer.data(), img.width, img.height, 0,
        outputBuffer.data(), newWidth, newHeight, 0,
        STBIR_RGB
    );

    // Parse Buffer
    std::vector<Pixel> resizedPixels;
    for (int i = 0; i < newWidth * newHeight; i++) {
        resizedPixels.push_back(Pixel{outputBuffer[i*3], outputBuffer[i*3+1], outputBuffer[i*3+2]});
    }

    // Create output Image struct
    Image resizedImage = { newWidth, newHeight, resizedPixels };

    return resizedImage;
}