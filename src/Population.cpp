#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include <string>
#include "Individual.h"
#include "Population.h"
#include "Utils.h"

Population::Population(int const initialPopulationSize, int const temporaryPopulationSize, double const mutationRate)
        : initialPopulationSize(initialPopulationSize),
          temporaryPopulationSize(temporaryPopulationSize),
          mutationRate(mutationRate) {
    initializePopulation();
}

Individual Population::oneGeneration() {
    this->clearTemporaryPopulations();
    this->createTemporaryPopulation();
    this->crossoverAndMutation();
    this->naturalSelection();

    return this->getBestIndividual();
}

void Population::initializePopulation() {
    for (int i = 0; i < initialPopulationSize; i++) {
        this->population.push_back(Individual::random());
    }
}

void Population::createTemporaryPopulation() {
    for (int i = 0; i < temporaryPopulationSize; i++) {
        int random = Utils::getRandomInt(0, initialPopulationSize);
        this->tempPopulationT.push_back(population[random]);
    }
}

Individual Population::getBestIndividual() {
    std::sort(population.begin(), population.end());
    return population[0];
}

void Population::crossoverAndMutation() {
    assert(tempPopulationR.size() == 0);

    for (int i = 0; i < temporaryPopulationSize; i++) {
        // crossover
        int a = Utils::getRandomInt(0, temporaryPopulationSize);
        int b = Utils::getRandomInt(0, temporaryPopulationSize);
        Individual partnerA = tempPopulationT[a];
        Individual partnerB = tempPopulationT[b];
        Individual child = partnerA.crossover(partnerB);

        // mutation
        child.mutate(mutationRate);

        tempPopulationR.push_back(child);
    }
}

void Population::naturalSelection() {
    tempPopulationR.insert(tempPopulationR.end(), population.begin(), population.end());
    std::sort(tempPopulationR.begin(), tempPopulationR.end());

    for (int i = 0; i < initialPopulationSize; i++) {
        population[i] = tempPopulationR[i];
    }
}

void Population::clearTemporaryPopulations() {
    this->tempPopulationT.clear();
    this->tempPopulationR.clear();
}

void Population::print(const std::vector<Individual>& population) {
    for (auto i : population) {
        std::cout << i.getX() << " [" << i.getFitness() << "], ";
    } std::cout << std::endl;
}

