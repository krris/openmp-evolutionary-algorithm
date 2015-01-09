#pragma once

#include <vector>

class Individual {
private:
    float value;
    float fitness;

    float calculateFitness();

public:
    Individual(float value);

    Individual crossover(const Individual & partner);
    void mutate(float mutationRate);

    float getFitness() const;
};