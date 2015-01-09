#include <iostream>
#include "Population.h"

int main() {
    const int GENERATION_NO = 10;

    Population population;
    for (int i = 0; i < GENERATION_NO; i++) {
        Individual bestIndividual = population.oneGeneration();
        std::cout << "Generation " << i << std::endl;
        std::cout << "Best individual: " << bestIndividual.getX() << std::endl;
        std::cout << "Best individual fitness: " << bestIndividual.getFitness() << std::endl;
        std::cout << "================================" << std::endl;
    }
}
