#!/bin/bash

#mkdir bin
#javac -d bin/ CriticalSection.java
#java -cp bin/ orcchg.CriticalSection
#rm -rf bin/

for file in *.cpp; do
  base=$(basename "$file")
  binary="${base%.*}"
  g++ -std=c++11 -I. -pthread -lm $file -o $binary
done

./n_readers_1_writer

rm ./n_readers_1_writer

