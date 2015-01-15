#include "Individual.h"
#include "Population.h"
#include <iostream>

Individual::Individual(double x) : x(x) {
    this->calculateFitness();
}

void Individual::calculateFitness() {
    int N = Individual::N;

    double sumOfXSquare = 0;
    double productOfCosSequence = 1;

    for (int i = 1; i <= N; i++) {
        double result = x * x;
        sumOfXSquare += result;

        double cos = std::cos(x/i);
        productOfCosSequence *= cos;
    }

    this->fitness = 1/40 * sumOfXSquare + 1 - productOfCosSequence;
}

double Individual::getFitness() const {
    return std::abs(this->fitness - Population::EXPECTED_VALUE);
}


double Individual::getX() const {
    return x;
}

Individual Individual::random() {
    std::random_device rd;
    std::default_random_engine e1(rd());
    std::uniform_real_distribution<double> uniform_dist(Individual::X_MIN, Individual::X_MAX);
    double x = uniform_dist(e1);
    return Individual(x);
}

Individual Individual::crossover(const Individual &partner) {
    double newX = partner.getX() + this->getX();
    if (newX == 0) {
        return 0;
    }
    newX /= 2;

    return Individual(newX);
}

void Individual::mutate(double mutationRate) {
    double random = getRandomDouble(0.0, 1.0);
    if (random < mutationRate) {
        double delta = getRandomDouble(0, MUTATE_MAX_RANGE);
        if (x > 0) {
            x -= delta;
        } else {
            x += delta;
        }
        calculateFitness();
    }
}

bool Individual::xIsInRange() {
    if (x >= X_MIN && x <= X_MAX) {
        return true;
    }
    return false;
}

int Individual::N = 3;

double Individual::getRandomDouble(double min, double max) {
    std::default_random_engine randomEngine;
    std::uniform_real_distribution<double> uniform_dist(min, max - 1);
    return uniform_dist(randomEngine);
}
