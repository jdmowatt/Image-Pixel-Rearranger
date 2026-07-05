#include "matcher.h"
#include <numeric>
#include <algorithm>
#include <iostream>
#include <random>

double brightness(const Pixel& p) {
    return 0.299*p.r + 0.587*p.g + 0.114*p.b;
}

std::vector<Pixel> matchBrightness(const std::vector<Pixel>& source, const std::vector<Pixel>& target) {
    std::cout << "Matching brightness ...\n";

    // Initialize order vectors
    std::vector<int> sourceOrder(source.size());
    std::vector<int> targetOrder(target.size());

    // Fill Vectors 0 - Size
    std::iota(sourceOrder.begin(), sourceOrder.end(), 0);
    std::iota(targetOrder.begin(), targetOrder.end(), 0);

    // Sort Order vectors by brightness
    std::sort(sourceOrder.begin(), sourceOrder.end(), [&](int a, int b) {
        return brightness(source[a]) < brightness(source[b]);
    });
    std::sort(targetOrder.begin(), targetOrder.end(), [&](int a, int b) {
        return brightness(target[a]) < brightness(target[b]);
    });

    // Match darkest pixel of source with darkest pixel of target into result, repeat
    std::vector<Pixel> result(target.size());
    for (size_t i = 0; i < target.size(); i++) {
        result[targetOrder[i]] = source[sourceOrder[i]];
    }

    return result;
}

////////////////////////////////////////////////////////

double colorDistance(const Pixel& a, const Pixel& b) {
    double dr = (double)a.r - b.r;
    double dg = (double)a.g - b.g;
    double db = (double)a.b - b.b;
    return dr*dr + dg*dg + db*db;
}

std::vector<Pixel> matchGreedy(const std::vector<Pixel>& source, const std::vector<Pixel>& target) {
    // Initialize Pool and Result Vectors
    std::vector<Pixel> pool = source;
    std::vector<int> shuffled(source.size());
    std::vector<Pixel> result(target.size());

    //Shuffle idxShuffle
    std::iota(shuffled.begin(), shuffled.end(), 0);
    std::mt19937 rng{std::random_device{}()};
    std::ranges::shuffle(shuffled, rng);


    // Find closest matching color pixel and remove it from pool, Repeat
    for (size_t i = 0; i < target.size(); i++) {
        int closest;
        double min = std::numeric_limits<double>::max();
        for (size_t j = 0; j < pool.size(); j++) {
            double distance = colorDistance(target[shuffled[i]], pool[j]);
            if (distance < min) {
                min = distance;
                closest = j;
            }
        }
        result[shuffled[i]] = pool[closest];
        pool[closest] = pool.back();
        pool.pop_back();
    }

    return result;
}