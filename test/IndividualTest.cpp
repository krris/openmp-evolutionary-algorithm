#include <boost/test/minimal.hpp>
#include "../Individual.h"
#include <log4cxx/basicconfigurator.h>

void calculateFitnessTest() {
    float expectedValue = 2;
    Individual individual(2);

    BOOST_CHECK (individual.getFitness() == expectedValue);
}

int test_main( int argc, char* argv[] )
{
    calculateFitnessTest();
    return 0;
}