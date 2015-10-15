#!/bin/bash

g++ -std=c++11 logging_sample_1.cpp -o logging_sample_1
g++ -std=c++11 logging_sample_2.cpp -o logging_sample_2
g++ -std=c++11 logging_sample_3.cpp -o logging_sample_3

./logging_sample_1 Hello
./logging_sample_2 World
./logging_sample_3

rm ./logging_sample_1
rm ./logging_sample_2
rm ./logging_sample_3

