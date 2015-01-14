#include <random>
#include "Utils.h"


double Utils::getRandomDouble(double min, double max) {
    // Seed with a real random value, if available
    std::random_device rd;

    // Choose a random between min and max
    std::default_random_engine e1(rd());
    std::uniform_real_distribution<double> uniform_dist(min, max - 1);
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

double Utils::fit(double x, int N) {
    double sumOfXSquare = 0;
    for (int i = 1; i <= N; i++) {
        double result = x * x;
        sumOfXSquare += result;
    }

    double productOfCosSequence = 1;
    for (int j = 1; j <= N; j++) {
        double cos = std::cos(x/j);
        productOfCosSequence *= cos;
    }

    return  1/40 * sumOfXSquare + 1 - productOfCosSequence;
}
