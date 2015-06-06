#!/bin/sh

generations=5000
initialPopulation=10000
tempPopulation=20000

build/before_profiling ${generations} ${initialPopulation} ${tempPopulation} 0.2 100 parallel
