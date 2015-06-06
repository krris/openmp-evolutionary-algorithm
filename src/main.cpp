#include <iostream>
#include "Population.h"
#include <omp.h>


int main(int argc, char* argv[]) {
    const int generationNo = atoi(argv[1]);
    const int initialPopulationSize = atoi(argv[2]);
    const int tempPopulationSize = atoi(argv[3]);
    const float mutationRate = atof(argv[4]);

    printf("Generations: %d\n", generationNo);
    printf("Initial population: %d\n", initialPopulationSize);
    printf("Temp population: %d\n", tempPopulationSize);


    Individual::N = atoi(argv[5]);
    std::string parallelArg = argv[6];
    bool parallel = false;
    if (parallelArg == "parallel") {
        parallel = true;
    }

    double start = omp_get_wtime();
    Population population(initialPopulationSize, tempPopulationSize, mutationRate, parallel);
    Individual bestIndividual = NULL;
    for (int i = 0; i < generationNo; i++) {
        bestIndividual = population.oneGeneration();
    }
    double finish = omp_get_wtime();
    double delta = finish - start;
    printf("%f\n", delta);
}


