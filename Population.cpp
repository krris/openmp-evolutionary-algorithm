#include "Individual.h"
#include "Population.h"

Individual Population::oneGeneration() {
    this->createTemporaryPopulation();
    this->crossoverAndMutation();
    this->naturalSelection();
    return this->getBestIndividual();
}

Individual Population::getBestIndividual() {
    // TODO
}

void Population::createTemporaryPopulation() {
    // TODO
}

void Population::crossoverAndMutation() {
    // TODO
}

void Population::naturalSelection() {
    // TODO
}
