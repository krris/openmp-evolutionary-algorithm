#!/bin/sh

delimiter="============================\n"

generations=100
title="Sequential version"

echo ${title} " [N = 2]"
build/PORR ${generations} 100 200 0.2 2
#echo ${delimiter}

echo ${title} " [N = 10]"
build/PORR ${generations} 100 200 0.2 10
#echo ${delimiter}

echo ${title} " [N = 20]"
build/PORR ${generations} 100 200 0.2 20
#echo ${delimiter}

echo ${title} " [N = 50]"
build/PORR ${generations} 100 200 0.2 50
#echo ${delimiter}

echo ${title} " [N = 100]"
build/PORR ${generations} 100 200 0.2 100
#echo ${delimiter}

