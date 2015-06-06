#!/bin/sh

generations=100
initialPopulation=10000
tempPopulation=20000

build/PORR ${generations} ${initialPopulation} ${tempPopulation} 0.2 100 parallel
