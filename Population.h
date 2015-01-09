#pragma once

#include <vector>
#include <random>
#include "Individual.h"

class Population {
private:
    const int INITIAL_POPULATION_SIZE = 5;
    const int TEMPORARY_POPULATION_SIZE = 10;
    const float MUTATION_RATE = 1.0;

    std::vector<Individual> population;
    std::vector<Individual> tempPopulationT;
    std::vector<Individual> tempPopulationR;

    int getRandomInt(int min, int max);

    void initializePopulation();
    void createTemporaryPopulation();
    void crossoverAndMutation();
    void naturalSelection();
    void clearTemporaryPopulations();
public:

    Population();
    const float LOWER_BOUND = -40.0;
    const float UPPER_BOUND = 40.0;

    static constexpr float EXPECTED_VALUE = 0.0;

    /* Returns best individual from one generation. */
    Individual oneGeneration();

    Individual getBestIndividual();
    static void print(std::vector<Individual> population);
};