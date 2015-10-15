#!/bin/bash

g++ -std=c++11 -I../logging statements_1.cpp -o statements_1
g++ -std=c++11 -I../logging statements_2.cpp -o statements_2
g++ -std=c++11 -I../logging statements_3.cpp -o statements_3
g++ -std=c++11 -I../logging statements_4.cpp -o statements_4
g++ -std=c++11 -I../logging statements_5.cpp -o statements_5
g++ -std=c++11 -I../logging statements_6.cpp -o statements_6
g++ -std=c++11 -I../logging statements_7.cpp -o statements_7
g++ -std=c++11 -I../logging statements_8.cpp -o statements_8
g++ -std=c++11 -I../logging statements_9.cpp -o statements_9

./statements_1
./statements_2
./statements_3
./statements_4
./statements_5
./statements_6
./statements_7
./statements_8
./statements_9

rm ./statements_1
rm ./statements_2
rm ./statements_3
rm ./statements_4
rm ./statements_5
rm ./statements_6
rm ./statements_7
rm ./statements_8
rm ./statements_9

