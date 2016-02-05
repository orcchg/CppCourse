#!/bin/bash

for file in *.cpp; do
  base=$(basename "$file")
  binary="${base%.*}"
  g++ -std=c++11 $file -o $binary
  ./$binary
  rm ./$binary
done

