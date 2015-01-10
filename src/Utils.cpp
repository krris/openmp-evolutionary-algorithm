#include <random>
#include "Utils.h"


float Utils::getRandomFloat(float min, float max) {
    // Seed with a real random value, if available
    std::random_device rd;

    // Choose a random between min and max
    std::default_random_engine e1(rd());
    std::uniform_real_distribution<float> uniform_dist(min, max - 1);
    return uniform_dist(e1);
}

int Utils::getRandomInt(int min, int max) {
    // Seed with a real random value, if available
    std::random_device rd;

    // Choose a random between min and max
    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(min, max - 1);
    return uniform_dist(e1);
}
