#pragma once

#include <vector>
#include <random>
#include "Individual.h"
#include "Utils.h"

//using namespace log4cxx;

class Population {
private:
    const int initialPopulationSize;
    const int temporaryPopulationSize;
    const double mutationRate;

    bool parallelVersion;

    std::vector<Individual> population;

    void initializePopulation();
    std::vector<Individual> createTemporaryPopulation(std::vector<Individual>& fromPopulation);
    std::vector<Individual> naturalSelection(std::vector<Individual> &populationA, std::vector<Individual> &populationB);
    std::vector<Individual> crossover(std::vector<Individual>& population);
    std::vector<Individual> mutation(std::vector<Individual> population);
    std::vector<Individual> crossoverParallel(std::vector<Individual>& population);
    std::vector<Individual> mutationParallel(std::vector<Individual> population);

    int getRandomInt(int min, int max);

public:

    Population(int const initialPopulationSize, int const temporaryPopulationSize, float const mutationRate, bool parallel);

    const double LOWER_BOUND = -40.0;
    const double UPPER_BOUND = 40.0;

    static constexpr double EXPECTED_VALUE = 0.0;

    /* Returns best individual from one generation. */
    Individual oneGeneration();

    Individual getBestIndividual(const std::vector<Individual> &population);
    Individual getBestIndividualParallel(const std::vector<Individual> &population);
    static void print(const std::vector<Individual>& population);

};