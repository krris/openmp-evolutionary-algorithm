#include <random>
#include "Utils.h"

double Utils::fitness(double x, int N) {
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
