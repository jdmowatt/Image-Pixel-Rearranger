#include <iostream>
#include "matcher.h"

int main(int argc, char* argv[]) {

    // Check for correct number of arguments
    if (argc != 3) {
        std::cout << "Error: Improper number of arguments.\n";
        std::cout << "Only add source and target files.\n";
        return 1;
    }

    // Load input files into program
    std::string sourceFile = argv[1];
    std::string targetFile = argv[2];

    Image a = loadImage(sourceFile);
    Image b = loadImage(targetFile);

    // Check if images are the same size
    if (a.width != b.width || a.height != b.height) {
        std::cout << "Error: Image dimensions must match exactly.\n";
        std::cout << "Source: " << a.width << "x" << a.height << "\n";
        std::cout << "Target: " << b.width << "x" << b.height << "\n";
        return 1;
    }

    // Run matcher algorithm to get result
    std::vector<Pixel> result = matchBrightness(a.pixels, b.pixels);

    // Initialize and save output image
    Image c = { b.width, b.height, result };
    saveImage("output.png", c);

    return 0;
}