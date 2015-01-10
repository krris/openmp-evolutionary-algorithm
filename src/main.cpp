#include <iostream>
#include "Population.h"
#include "Utils.h"

int main(int argc, char* argv[]) {

    const int generationNo = atoi(argv[1]);
    const int initialPopulationSize = atoi(argv[2]);
    const int tempPopulationSize = atoi(argv[3]);
    const float mutationRate = atof(argv[4]);

    Population population(initialPopulationSize, tempPopulationSize, mutationRate);
    for (int i = 0; i < generationNo; i++) {
        Individual bestIndividual = population.oneGeneration();
        std::cout << "Generation " << i << std::endl;
        std::cout << "Best individual: " << bestIndividual.getX() << std::endl;
        std::cout << "Best individual fitness: " << bestIndividual.getFitness() << std::endl;
        std::cout << "================================" << std::endl;
    }
}
