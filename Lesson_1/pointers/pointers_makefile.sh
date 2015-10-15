#!/bin/bash

g++ -std=c++11 -I../logging pointers_1.cpp -o pointers_1
g++ -std=c++11 -I../logging pointers_2.cpp -o pointers_2
g++ -std=c++11 -I../logging pointers_3.cpp -o pointers_3
g++ -std=c++11 -I../logging pointers_4.cpp -o pointers_4
g++ -std=c++11 -I../logging pointers_5.cpp -o pointers_5
g++ -std=c++11 -I../logging pointers_6.cpp -o pointers_6
g++ -std=c++11 -I../logging pointers_7.cpp -o pointers_7
g++ -std=c++11 -I../logging pointers_8.cpp -o pointers_8

./pointers_1
./pointers_2
./pointers_3
./pointers_4
./pointers_5
./pointers_6
./pointers_7
./pointers_8

rm ./pointers_1
rm ./pointers_2
rm ./pointers_3
rm ./pointers_4
rm ./pointers_5
rm ./pointers_6
rm ./pointers_7
rm ./pointers_8

