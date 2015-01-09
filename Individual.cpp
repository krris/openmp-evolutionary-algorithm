#include "Individual.h"
#include "Population.h"
#include <cmath>

float Individual::calculateFitness() {
    return std::abs(this->value - Population::EXPECTED_VALUE);
}

float Individual::getFitness() const {
    return fitness;
}

Individual::Individual(float value) : value(value) {}

