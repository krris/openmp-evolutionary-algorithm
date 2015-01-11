#include <iostream>
#include "Population.h"
#include <omp.h>
//#include <log4cxx/basicconfigurator.h>

//using namespace log4cxx;

int main(int argc, char* argv[]) {
//    BasicConfigurator::configure();
//    LOG4CXX_INFO(Logger::getRootLogger(), "Program started.");

    #pragma omp parallel
    printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());

    const int generationNo = atoi(argv[1]);
    const int initialPopulationSize = atoi(argv[2]);
    const int tempPopulationSize = atoi(argv[3]);
    const float mutationRate = atof(argv[4]);
    Individual::N = atoi(argv[5]);

    Population population(initialPopulationSize, tempPopulationSize, mutationRate);
    for (int i = 0; i < generationNo; i++) {
        Individual bestIndividual = population.oneGeneration();
        std::cout << "Generation " << i << std::endl;
        std::cout << "Best individual: " << bestIndividual.getX() << std::endl;
        std::cout << "Best individual fitness: " << bestIndividual.getFitness() << std::endl;
        std::cout << "================================" << std::endl;
    }
}
