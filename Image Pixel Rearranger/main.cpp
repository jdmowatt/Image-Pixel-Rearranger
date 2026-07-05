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

    // Check if images are the same size, if not resizes the larger one.
    if (a.width != b.width || a.height != b.height) {
        std::cout << "Resizing.\n";
        long long aCount = (long long)a.width * a.height;
        long long bCount = (long long)b.width * b.height;

        if (aCount > bCount) {
            a = resizeImage(a, b.width, b.height);
        } else {
            b = resizeImage(b, a.width, a.height);
        }
    }

    // Run matcher algorithm to get result
    std::vector<Pixel> result = matchBrightness(a.pixels, b.pixels);

    // Initialize and save output image
    Image c = { b.width, b.height, result };
    saveImage("output.png", c);

    return 0;
}