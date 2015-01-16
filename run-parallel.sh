#!/bin/sh

delimiter="============================\n"

generations=100
initialPopulation=10000
tempPopulation=20000
title="Parallel version"

echo ${title} " [N = 2]"
build/PORR ${generations} ${initialPopulation} ${tempPopulation} 0.2 2 parallel
#echo ${delimiter}

echo ${title} " [N = 10]"
build/PORR ${generations} ${initialPopulation} ${tempPopulation} 0.2 10 parallel
#echo ${delimiter}

echo ${title} " [N = 20]"
build/PORR ${generations} ${initialPopulation} ${tempPopulation} 0.2 20 parallel
#echo ${delimiter}

echo ${title} " [N = 50]"
build/PORR ${generations} ${initialPopulation} ${tempPopulation} 0.2 50 parallel
#echo ${delimiter}

echo ${title} " [N = 100]"
build/PORR ${generations} ${initialPopulation} ${tempPopulation} 0.2 100 parallel
#echo ${delimiter}

