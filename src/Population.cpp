#include <algorithm>
#include <iostream>
#include <cassert>
#include "Individual.h"
#include "Population.h"
#include <omp.h>

Population::Population(int const initialPopulationSize, int const temporaryPopulationSize, float const mutationRate, bool b)
        : initialPopulationSize(initialPopulationSize),
          temporaryPopulationSize(temporaryPopulationSize),
          mutationRate(mutationRate),
          parallelVersion(b) {
    initializePopulation();
}

Individual Population::oneGeneration() {
    if (!parallelVersion) {
        std::vector<Individual> temporaryPopulation = this->crossover(this->population);
        temporaryPopulation = this->mutation(temporaryPopulation);
        this->population = this->naturalSelection(this->population, temporaryPopulation);
        return this->getBestIndividual(this->population);
    }
    std::vector<Individual> temporaryPopulation = this->crossoverParallel(this->population);
    temporaryPopulation = this->mutationParallel(temporaryPopulation);
    this->population = this->naturalSelection(this->population, temporaryPopulation);
    return this->getBestIndividualParallel(this->population);
}

void Population::initializePopulation() {
    for (int i = 0; i < initialPopulationSize; i++) {
        this->population.push_back(Individual::random());
    }
}

std::vector<Individual> Population::createTemporaryPopulation(std::vector<Individual>& fromPopulation) {
    std::vector<Individual> tempPopulation;
    tempPopulation.reserve(temporaryPopulationSize);

    for (int i = 0; i < temporaryPopulationSize; i++) {
        int random = getRandomInt(0, initialPopulationSize);
        tempPopulation.push_back(fromPopulation[random]);
    }
    return tempPopulation;
}

Individual Population::getBestIndividualParallel(const std::vector<Individual> &population) {
    double sharedMinValue = std::numeric_limits<double>::max();
    Individual sharedBestIndividual = NULL;

    #pragma omp parallel
    {
        double minValue = std::numeric_limits<double>::max();
        Individual bestLocalIndividual = NULL;
        #pragma omp for nowait
        for(int i = 0; i < population.size(); i++){
            double fitness = population[i].getFitness();
            if (fitness < minValue) {
                minValue = fitness;
                bestLocalIndividual = population[i];
            }
        }

        #pragma omp critical
        {
            if (minValue < sharedMinValue) {
                sharedMinValue = minValue;
                sharedBestIndividual = bestLocalIndividual;
            }
        }
    }

    return sharedBestIndividual;
}

Individual Population::getBestIndividual(const std::vector<Individual> &population) {
    return *(std::min_element(population.begin(), population.end()));
}

std::vector<Individual> Population::crossover(std::vector<Individual>& population) {
    assert (population.size() > 0);
    const int size = temporaryPopulationSize;
    std::vector<Individual> tempPopulationT = createTemporaryPopulation(population);
    std::vector<Individual> tempPopulationR(size, NULL);

    for (int i = 0; i < size; i++) {
        int a = getRandomInt(0, size);
        int b = getRandomInt(0, size);
        Individual partnerA = tempPopulationT[a];
        Individual partnerB = tempPopulationT[b];
        Individual child = partnerA.crossover(partnerB);

        assert (i < size);
        tempPopulationR[i] = child;
    }

    return tempPopulationR;
}


std::vector<Individual> Population::crossoverParallel(std::vector<Individual> &population) {
    assert (population.size() > 0);

    std::vector<Individual> tempPopulationR;
    tempPopulationR.reserve(temporaryPopulationSize);

    #pragma omp parallel
    {
        const int size = temporaryPopulationSize;
        std::vector<Individual> tempPopulationT = createTemporaryPopulation(population);
        std::vector<Individual> localPopulation;
        localPopulation.reserve(size / omp_get_num_threads());

        for (int i = omp_get_thread_num(); i < size; i += omp_get_num_threads()) {
            int a = getRandomInt(0, size);
            int b = getRandomInt(0, size);
            Individual partnerA = tempPopulationT[a];
            Individual partnerB = tempPopulationT[b];
            Individual child = partnerA.crossover(partnerB);
            localPopulation.push_back(child);
            assert (i < size);
        }

        #pragma omp critical
        tempPopulationR.insert(tempPopulationR.end(), localPopulation.begin(), localPopulation.end());
    }
    return tempPopulationR;
}

std::vector<Individual> Population::mutation(std::vector<Individual> population) {
    const int size = temporaryPopulationSize;
    const double mutationRate = this->mutationRate;

    for (int i = 0; i < size; i++) {
        population[i].mutate(mutationRate);
    }
    return population;
}

std::vector<Individual> Population::mutationParallel(std::vector<Individual> population) {
    const int size = temporaryPopulationSize;
    const double mutationRate = this->mutationRate;

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        population[i].mutate(mutationRate);
    }
    return population;
}

std::vector<Individual> Population::naturalSelection(std::vector<Individual> &populationA, std::vector<Individual> &populationB) {

    std::vector<Individual> tempPopulation;
    tempPopulation.reserve(populationA.size() + populationB.size());
    tempPopulation.insert(tempPopulation.end(), populationA.begin(), populationA.end());
    tempPopulation.insert(tempPopulation.end(), populationB.begin(), populationB.end());

    std::sort(tempPopulation.begin(), tempPopulation.end());

    std::vector<Individual> selectedPopulation;
    selectedPopulation.reserve(initialPopulationSize);
    for (int i = 0; i < initialPopulationSize; i++) {
        selectedPopulation.push_back(tempPopulation[i]);
    }
    return selectedPopulation;
}

void Population::print(const std::vector<Individual>& population) {
    std::cout << "Thread [" << omp_get_thread_num() << "] ";
    for (auto i : population) {
        std::cout << i.getX() << " [" << i.getFitness() << "], ";
    } std::cout << std::endl;
}


int Population::getRandomInt(int min, int max) {
    std::default_random_engine randomEngine;
    std::uniform_int_distribution<int> uniform_dist(min, max - 1);
    return uniform_dist(randomEngine);
}
