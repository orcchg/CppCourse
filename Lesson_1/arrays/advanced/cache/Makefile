#!/bin/bash

for file in *.cpp; do
  base=$(basename "$file")
  binary="${base%.*}"
  #g++ -std=c++11 -I../include $file -o $binary
  #./$binary
  #rm ./$binary
done

g++ -std=c++11 -I../include cache_estimate.cpp -o cache_estimate
./cache_estimate
rm ./cache_estimate

