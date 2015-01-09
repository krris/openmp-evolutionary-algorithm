#include <algorithm>
#include <vector>
#include <iostream>
#include "Individual.h"
#include "Population.h"

Population::Population() {
    initializePopulation();
}

Individual Population::oneGeneration() {
    std::cout << "Start of one generation" << std::endl;
    this->print(population);


    this->clearTemporaryPopulations();
    this->createTemporaryPopulation();
    this->crossoverAndMutation();
    this->naturalSelection();

    std::cout << "End of one generation" << std::endl;
    this->print(population);

    return this->getBestIndividual();

}

void Population::initializePopulation() {
    for (int i = 0; i < INITIAL_POPULATION_SIZE; i++) {
        this->population.push_back(Individual::random());
    }
}

void Population::createTemporaryPopulation() {
    for (int i = 0; i < TEMPORARY_POPULATION_SIZE; i++) {
        int random = getRandomInt(0, INITIAL_POPULATION_SIZE - 1);
        this->tempPopulationT.push_back(population[random]);
    }
}

Individual Population::getBestIndividual() {
    // TODO
}

void Population::crossoverAndMutation() {
    for (int i = 0; i < TEMPORARY_POPULATION_SIZE; i++) {
        // crossover
        int a = getRandomInt(0, TEMPORARY_POPULATION_SIZE);
        int b = getRandomInt(0, TEMPORARY_POPULATION_SIZE);
        Individual partnerA = tempPopulationT[a];
        Individual partnerB = tempPopulationT[b];
        Individual child = partnerA.crossover(partnerB);

        // mutation
        child.mutate(MUTATION_RATE);

        tempPopulationR.push_back(child);
    }
}

void Population::naturalSelection() {
    tempPopulationR.insert(tempPopulationR.end(), population.begin(), population.end());
    std::sort(tempPopulationR.begin(), tempPopulationR.end());

    for (int i = 0; i < INITIAL_POPULATION_SIZE; i++) {
        population[i] = tempPopulationR[i];
    }
}

int Population::getRandomInt(int min, int max) {
    // Seed with a real random value, if available
    std::random_device rd;

    // Choose a random between min and max
    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(min, max);
    return uniform_dist(e1);
}

void Population::clearTemporaryPopulations() {
    this->tempPopulationT.clear();
    this->tempPopulationR.clear();
}

void Population::print(std::vector<Individual> population) {
    for (auto i : population) {
        std::cout << i.getX() << " [" << i.getFitness() << "], ";
    } std::cout << std::endl;
}
