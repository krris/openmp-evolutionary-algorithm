//#include <boost/test/minimal.hpp>
#include "../src/Individual.h"

void calculateFitnessTest() {
    float expectedValue = 2;
    Individual individual(2);

//    BOOST_CHECK (individual.getFitness() == expectedValue);
}

int test_main( int argc, char* argv[] )
{
//    BOOST_LOG_TRIVIAL(info) << "Logger test";
    calculateFitnessTest();

    return 0;
}