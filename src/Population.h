#pragma once

#include <vector>
#include <random>
//#include <log4cxx/logger.h>
#include "Individual.h"
#include "Utils.h"

//using namespace log4cxx;

class Population {
private:
    const int initialPopulationSize;
    const int temporaryPopulationSize;
    const double mutationRate;

    std::vector<Individual> population;
    std::vector<Individual> tempPopulationT;
    std::vector<Individual> tempPopulationR;

    void initializePopulation();
    void createTemporaryPopulation();
    void crossoverAndMutation();
    void naturalSelection();
    void clearTemporaryPopulations();
public:

    Population(int const initialPopulationSize, int const temporaryPopulationSize, double const mutationRate);

    const double LOWER_BOUND = -40.0;
    const double UPPER_BOUND = 40.0;

    static constexpr double EXPECTED_VALUE = 0.0;

    /* Returns best individual from one generation. */
    Individual oneGeneration();

    Individual getBestIndividual();
    static void print(const std::vector<Individual>& population);

    void crossover();

    void mutation();
};