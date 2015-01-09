#pragma once

#include <vector>
#include "Individual.h"

class Population {
private:
    const int POPULATION_MAX = 100;
    const float ALPHA = 1.0;
    const float MUTATION_RATE = 0.2;

    std::vector<Individual> population;
    std::vector<Individual> tempPopulationT;
    std::vector<Individual> tempPopulationR;

    void createTemporaryPopulation();
    void crossoverAndMutation();
    void naturalSelection();

public:
    const float LOWER_BOUND = -40.0;
    const float UPPER_BOUND = 40.0;
    static constexpr float EXPECTED_VALUE = 0.0;

    /* Returns best individual from one generation. */
    Individual oneGeneration();

    Individual getBestIndividual();
};