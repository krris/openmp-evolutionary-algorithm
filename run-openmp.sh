#!/bin/sh

delimiter="============================\n"

echo "Wersja openmp [N = 2]"
time pwd
echo ${delimiter}

echo "Wersja openmp [N = 10]"
time pwd
echo ${delimiter}

echo "Wersja openmp [N = 20]"
time pwd
echo ${delimiter}

echo "Wersja openmp [N = 50]"
time pwd
echo ${delimiter}

echo "Wersja openmp [N = 100]"
time pwd
echo ${delimiter}

