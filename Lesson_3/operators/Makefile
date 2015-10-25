#!/bin/bash

for file in *.cpp; do
  base=$(basename "$file")
  binary="${base%.*}"
  g++ -std=c++11 -I../include $file -o $binary
done

