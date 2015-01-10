#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include "Individual.h"
#include "Population.h"
#include "Utils.h"

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
        int random = Utils::getRandomInt(0, INITIAL_POPULATION_SIZE);
        this->tempPopulationT.push_back(population[random]);
    }
}

Individual Population::getBestIndividual() {
    std::sort(population.begin(), population.end());
    return population[0];
}

void Population::crossoverAndMutation() {
    assert(tempPopulationR.size() == 0);

    for (int i = 0; i < TEMPORARY_POPULATION_SIZE; i++) {
        // crossover
        int a = Utils::getRandomInt(0, TEMPORARY_POPULATION_SIZE);
        int b = Utils::getRandomInt(0, TEMPORARY_POPULATION_SIZE);
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

void Population::clearTemporaryPopulations() {
    this->tempPopulationT.clear();
    this->tempPopulationR.clear();
}

void Population::print(std::vector<Individual> population) {
    for (auto i : population) {
        std::cout << i.getX() << " [" << i.getFitness() << "], ";
    } std::cout << std::endl;
}
