#!/bin/bash
# Author : Rajat Khanduja
# Scipt to run the benchmarking program K number of times (K is user-defined).

prog=$1
K=$2

executable=${prog%.*}.out

gcc $1 -o executable

rm -f results
while [ $K -gt 0 ]
do
   ./executable >> results  
   K=$((K-1))
done
rm executable
