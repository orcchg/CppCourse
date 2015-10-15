#!/bin/bash

for file in *.cpp; do
  base=$(basename "$file")
  binary="${base%.*}"
  g++ -std=c++11 -I.. $file -o $binary
# g++ -std=c++11 -I.. -ggdb3 -O0 $file -o $binary
  ./$binary
  rm ./$binary
done

