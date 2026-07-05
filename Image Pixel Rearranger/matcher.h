#pragma once
#include "image_io.h"

// Returns a new set of pixels, same size as target,
// built only from source's pixels, arranged to resemble target.

// Brightness Matching Algorithm
std::vector<Pixel> matchBrightness(const std::vector<Pixel>& source, const std::vector<Pixel>& target);

// Greedy Nearest-Color Matching Algorithm (SLOW)
std::vector<Pixel> matchGreedy(const std::vector<Pixel>& source, const std::vector<Pixel>& target);