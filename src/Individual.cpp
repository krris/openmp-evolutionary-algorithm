#include "Individual.h"
#include "Population.h"
#include "Utils.h"
#include <iostream>

Individual::Individual(float x) : x(x) {
    this->calculateFitness();
}

void Individual::calculateFitness() {
    float sumOfXSquare = 0;
    for (int i = 1; i <= this->n; i++) {
        sumOfXSquare += x * x;
    }

    float productOfCosSequence = 1;
    for (int i = 1; i <= this->n; i++) {
        productOfCosSequence *= std::cos(x/i);
    }

    this->fitness = 1/40 * sumOfXSquare + 1 - productOfCosSequence;
}

float Individual::getFitness() const {
    return std::abs(this->fitness - Population::EXPECTED_VALUE);
}


float Individual::getX() const {
    return x;
}

Individual Individual::random() {
    std::random_device rd;
    std::default_random_engine e1(rd());
    std::uniform_real_distribution<float> uniform_dist(Individual::X_MIN, Individual::X_MAX);
    float x = uniform_dist(e1);

    std::cout << "Random individual: " << x << std::endl;

    return Individual(x);
}

Individual Individual::crossover(const Individual &partner) {
    float newX = partner.getX() + this->getX();
    if (newX == 0) {
        printf("== newX = 0 (%f + %f)\n", this->getX(), partner.getX());
        return 0;
    }
    newX /= 2;

    printf("Crossover: %f + %f = %f\n", getX(), partner.getX(), newX);
    return Individual(newX);
}

void Individual::mutate(float mutationRate) {
    float random = Utils::getRandomFloat(0.0, 1.0);
    if (random < mutationRate) {
        printf("Mutation of %f - ", getX());
        do {
            float delta = Utils::getRandomFloat(-1.0, 1.0);
            x += delta;
        } while (!xIsInRange());
        printf("new value: %f\n", getX());
    }
}

bool Individual::xIsInRange() {
    if (x >= X_MIN && x <= X_MAX) {
        return true;
    }
    return false;
}
