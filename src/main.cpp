#include <iostream>
#include "Population.h"
#include <omp.h>
double fit(double x, int N);

int main(int argc, char* argv[]) {
    const int generationNo = atoi(argv[1]);
    const int initialPopulationSize = atoi(argv[2]);
    const int tempPopulationSize = atoi(argv[3]);
    const float mutationRate = atof(argv[4]);
    Individual::N = atoi(argv[5]);

    double start = omp_get_wtime();
    Population population(initialPopulationSize, tempPopulationSize, mutationRate);
    Individual bestIndividual = NULL;
    for (int i = 0; i < generationNo; i++) {
        bestIndividual = population.oneGeneration();
    }
    double finish = omp_get_wtime();
    double delta = finish - start;
    printf("Time: %f\n", delta);
    std::cout << "Best individual: " << bestIndividual.getX() << std::endl;
    std::cout << "Best individual fitness: " << bestIndividual.getFitness() << std::endl;
    printf("Expected fitness = %f\n", fit(bestIndividual.getX(), Individual::N));
    std::cout << "================================" << std::endl;


}

double fit(double x, int N) {
    double sumOfXSquare = 0;
    for (int i = 1; i <= N; i++) {
        double result = x * x;
        sumOfXSquare += result;
    }

    double productOfCosSequence = 1;
    for (int j = 1; j <= N; j++) {
        double cos = std::cos(x/j);
        productOfCosSequence *= cos;
    }

    return  1/40 * sumOfXSquare + 1 - productOfCosSequence;
}
