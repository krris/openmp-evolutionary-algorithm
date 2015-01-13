#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include <string>
#include "Individual.h"
#include "Population.h"
#include "Utils.h"
#include <omp.h>

Population::Population(int const initialPopulationSize, int const temporaryPopulationSize, double const mutationRate)
        : initialPopulationSize(initialPopulationSize),
          temporaryPopulationSize(temporaryPopulationSize),
          mutationRate(mutationRate) {
    initializePopulation();
}

Individual Population::oneGeneration() {
    this->clearTemporaryPopulations();
    this->createTemporaryPopulation();
    this->crossover();
    this->mutation();
//    this->crossoverAndMutation();
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
    // TODO do zrównoleglenia
    std::sort(population.begin(), population.end());
    return population[0];
}

void Population::crossover() {

    assert(tempPopulationR.size() == 0);

    std::vector<Individual> localTempPopulationR(this->tempPopulationR);
    std::vector<Individual> localTempPopulationT(this->tempPopulationT);
    int size = temporaryPopulationSize;

    for (int i = 0; i < size; i++) {
        // crossover
        int a = Utils::getRandomInt(0, size);
        int b = Utils::getRandomInt(0, size);
        Individual partnerA = localTempPopulationT[a];
        Individual partnerB = localTempPopulationT[b];
        Individual child = partnerA.crossover(partnerB);

        localTempPopulationR.push_back(child);
    }
    tempPopulationR = localTempPopulationR;
//    printf("Test individual value = %f\n", tempPopulationR[0].getX());

}

void Population::mutation() {
    for (int i = 0; i < temporaryPopulationSize; i++) {
        tempPopulationR[i].mutate(mutationRate);
//        printf("test: %f\n", tempPopulationR[i].getX());
    }
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

