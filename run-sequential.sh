#!/bin/sh

delimiter="============================\n"

generations=100
initialPopulation=10000
tempPopulation=20000
title="Sequential version"

echo ${title} " [N = 2]"
build/PORR ${generations} ${initialPopulation} ${tempPopulation} 0.2 2 sequantial
#echo ${delimiter}

echo ${title} " [N = 10]"
build/PORR ${generations} ${initialPopulation} ${tempPopulation} 0.2 10 sequential
#echo ${delimiter}

echo ${title} " [N = 20]"
build/PORR ${generations} ${initialPopulation} ${tempPopulation} 0.2 20 sequential
#echo ${delimiter}

echo ${title} " [N = 50]"
build/PORR ${generations} ${initialPopulation} ${tempPopulation} 0.2 50 sequential
#echo ${delimiter}

echo ${title} " [N = 100]"
build/PORR ${generations} ${initialPopulation} ${tempPopulation} 0.2 100 sequential
#echo ${delimiter}

