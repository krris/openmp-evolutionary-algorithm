#pragma once

#include <vector>
#include <random>
#include "Individual.h"

class Population {
private:
    const int initialPopulationSize;
    const int temporaryPopulationSize;
    const float mutationRate;

    std::vector<Individual> population;
    std::vector<Individual> tempPopulationT;
    std::vector<Individual> tempPopulationR;

    void initializePopulation();
    void createTemporaryPopulation();
    void crossoverAndMutation();
    void naturalSelection();
    void clearTemporaryPopulations();
public:

    Population(int const initialPopulationSize, int const temporaryPopulationSize, float const mutationRate);

    const float LOWER_BOUND = -40.0;
    const float UPPER_BOUND = 40.0;

    static constexpr float EXPECTED_VALUE = 0.0;

    /* Returns best individual from one generation. */
    Individual oneGeneration();

    Individual getBestIndividual();
    static void print(std::vector<Individual> population);
};