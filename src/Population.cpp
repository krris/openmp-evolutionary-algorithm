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
    printf("Befor crossover:\n");
    print(this->population);
    std::vector<Individual> temporaryPopulation = this->crossover(this->population);
    printf("After crossover:\n");
    print(temporaryPopulation);
    temporaryPopulation = this->mutation(temporaryPopulation);
    printf("Natural selection:\n");
    this->population = this->naturalSelection(this->population, temporaryPopulation);

    return this->getBestIndividual(this->population);
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
        int random = Utils::getRandomInt(0, initialPopulationSize);
        tempPopulation.push_back(fromPopulation[random]);
    }
    return tempPopulation;
}

Individual Population::getBestIndividual(const std::vector<Individual> &population) {
    double sharedMinValue = std::numeric_limits<double>::max();
    Individual sharedBestIndividual = NULL;
//    print(population);
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
                printf("Best ind: %f, fitness %f\n", sharedBestIndividual.getX(), sharedBestIndividual.getFitness());
            }
        }
    }

    return sharedBestIndividual;

//    std::max_element(population.begin(), population.end());
//    std::sort(population.begin(), population.end());
//    return population[0];
}

std::vector<Individual> Population::crossover(std::vector<Individual>& population) {

    const int size = temporaryPopulationSize;
    std::vector<Individual> tempPopulationT = createTemporaryPopulation(population);
    std::vector<Individual> tempPopulationR(size, NULL);

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        int a = Utils::getRandomInt(0, size);
        int b = Utils::getRandomInt(0, size);
        printf("size = %d, popSize = %d\n", size, population.size());
        Individual partnerA = tempPopulationT[a];
        Individual partnerB = tempPopulationT[b];
        Individual child = partnerA.crossover(partnerB);

        assert (i < size);
        tempPopulationR[i] = child;
    }

    return tempPopulationR;
//    printf("Test individual value = %f\n", tempPopulationR[0].getX());

}

std::vector<Individual> Population::mutation(std::vector<Individual> population) {
    const int size = temporaryPopulationSize;

    #pragma omp parallel for default(none) shared(population)
    for (int i = 0; i < size; i++) {
//        printf("i = %d [id: %d]\n", i, omp_get_thread_num());
        population[i].mutate(mutationRate);
    }

//    printf("===============\n");
    return population;
}

//void Population::crossoverAndMutation() {
//    assert(tempPopulationR.size() == 0);
//
//    for (int i = 0; i < temporaryPopulationSize; i++) {
//        // crossover
//        int a = Utils::getRandomInt(0, temporaryPopulationSize);
//        int b = Utils::getRandomInt(0, temporaryPopulationSize);
//        Individual partnerA = tempPopulationT[a];
//        Individual partnerB = tempPopulationT[b];
//        Individual child = partnerA.crossover(partnerB);
//s
//        // mutation
//        child.mutate(mutationRate);
//
//        tempPopulationR.push_back(child);
//    }
//}

std::vector<Individual> Population::naturalSelection(std::vector<Individual> &populationA, std::vector<Individual> &populationB) {

    std::vector<Individual> tempPopulation;
    tempPopulation.reserve(populationA.size() + populationB.size());
    printf("Size: %d, ", tempPopulation.size());
    tempPopulation.insert(tempPopulation.end(), populationA.begin(), populationA.end());
    tempPopulation.insert(tempPopulation.end(), populationB.begin(), populationB.end());
    printf("Size: %d\n", tempPopulation.size());
    print(tempPopulation);
    std::sort(tempPopulation.begin(), tempPopulation.end());
    print(tempPopulation);

    std::vector<Individual> selectedPopulation;
    selectedPopulation.reserve(initialPopulationSize);
    for (int i = 0; i < initialPopulationSize; i++) {
        selectedPopulation.push_back(tempPopulation[i]);
    }
    return selectedPopulation;
}

//void Population::clearTemporaryPopulations() {
//    this->tempPopulationT.clear();
//    this->tempPopulationR.clear();
//}

void Population::print(const std::vector<Individual>& population) {
    for (auto i : population) {
        std::cout << i.getX() << " [" << i.getFitness() << "], ";
    } std::cout << std::endl;
}

