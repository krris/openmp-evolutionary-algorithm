#include "Individual.h"
#include "Population.h"
#include "Utils.h"
#include <iostream>

Individual::Individual(double x) : x(x) {
    this->calculateFitness();
}

void Individual::calculateFitness() {
    double sumOfXSquare = 0;
    for (int i = 1; i <= this->n; i++) {
        sumOfXSquare += x * x;
    }

    double productOfCosSequence = 1;
    for (int i = 1; i <= this->n; i++) {
        productOfCosSequence *= std::cos(x/i);
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
//        printf("== newX = 0 (%f + %f)\n", this->getX(), partner.getX());
        return 0;
    }
    newX /= 2;

//    printf("Crossover: %f + %f = %f\n", getX(), partner.getX(), newX);
    return Individual(newX);
}

void Individual::mutate(double mutationRate) {
    double random = Utils::getRandomDouble(0.0, 1.0);
    if (random < mutationRate) {
//        printf("Mutation of %f - ", getX());
        do {
            double delta = Utils::getRandomDouble(MUTATE_MIN_RANGE, MUTATE_MAX_RANGE);
            x += delta;
        } while (!xIsInRange());
//        printf("new value: %f\n", getX());
    }
}

bool Individual::xIsInRange() {
    if (x >= X_MIN && x <= X_MAX) {
        return true;
    }
    return false;
}
