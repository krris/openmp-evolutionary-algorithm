#pragma once

#include <vector>
#include <random>

class Individual {
private:
    static constexpr double X_MIN = (- 40.0);
    static constexpr double X_MAX = 40.0;

    static constexpr double MUTATE_MIN_RANGE = -0.1;
    static constexpr double MUTATE_MAX_RANGE = 0.1;


    double x;
    double fitness;
    void calculateFitness();

public:
    static int N;
    Individual(double x);

    Individual crossover(const Individual & partner);
    void mutate(double mutationRate);

    static Individual random();

    double getFitness() const;
    double getX() const;

    bool operator < (const Individual& other) const
    {
        return (getFitness() < other.getFitness());
    }

    double getRandomDouble(double min, double max);
    bool xIsInRange();
};

