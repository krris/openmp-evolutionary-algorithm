#pragma once

#include <vector>
#include <random>

class Individual {
private:
    static const int DEFAULT_N = 2;
    static constexpr float X_MIN = (- 40.0);
    static constexpr float X_MAX = 40.0;

    float x;
    float fitness;
    int n = DEFAULT_N;

    void calculateFitness();

public:
    Individual(float x);

    Individual crossover(const Individual & partner);
    void mutate(float mutationRate);

    static Individual random();

    float getFitness() const;
    float getX() const;

    bool operator < (const Individual& other) const
    {
        // TODO check
        return (getFitness() < other.getFitness());
    }

    bool xIsInRange();
};