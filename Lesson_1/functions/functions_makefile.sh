#!/bin/bash

g++ -std=c++11 -I../logging functions_1.cpp -o functions_1
g++ -std=c++11 -I../logging functions_2.cpp -o functions_2
g++ -std=c++11 -I../logging functions_3.cpp -o functions_3
g++ -std=c++11 -I../logging functions_4.cpp -o functions_4
g++ -std=c++11 -I../logging functions_5.cpp -o functions_5
g++ -std=c++11 -I../logging functions_6.cpp -o functions_6
g++ -std=c++11 -I../logging functions_7.cpp -o functions_7
g++ -std=c++11 -I../logging functions_8.cpp -o functions_8
g++ -std=c++11 -I../logging functions_9.cpp -o functions_9
g++ -std=c++11 -I../logging functions_10.cpp -o functions_10
g++ -std=c++11 -I../logging functions_11.cpp -o functions_11

./functions_1
./functions_2 "Hello, World"
./functions_3 200
./functions_4 200
./functions_5
./functions_6
./functions_7
./functions_8
./functions_9
./functions_10
./functions_11

rm ./functions_1
rm ./functions_2
rm ./functions_3
rm ./functions_4
rm ./functions_5
rm ./functions_6
rm ./functions_7
rm ./functions_8
rm ./functions_9
rm ./functions_10
rm ./functions_11

