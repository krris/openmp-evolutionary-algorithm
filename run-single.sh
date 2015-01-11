#!/bin/sh

delimiter="============================\n"

generations=1000

echo "Wersja sekwencyjna [N = 2]"
time build/PORR ${generations} 100 200 0.2 2
echo ${delimiter}

echo "Wersja sekwencyjna [N = 10]"
time build/PORR ${generations} 100 200 0.2 10
echo ${delimiter}

echo "Wersja sekwencyjna [N = 20]"
time build/PORR ${generations} 100 200 0.2 20
echo ${delimiter}

echo "Wersja sekwencyjna [N = 50]"
time build/PORR ${generations} 100 200 0.2 50
echo ${delimiter}

echo "Wersja sekwencyjna [N = 100]"
time build/PORR ${generations} 100 200 0.2 100
echo ${delimiter}

