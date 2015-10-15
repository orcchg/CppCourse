#!/bin/bash

g++ -std=c++11 -I../logging arrays_1.cpp -o arrays_1
g++ -std=c++11 -I../logging arrays_2.cpp -o arrays_2
g++ -std=c++11 -I../logging arrays_3.cpp -o arrays_3
g++ -std=c++11 -I../logging arrays_4.cpp -o arrays_4
g++ -std=c++11 -I../logging arrays_5.cpp -o arrays_5
g++ -std=c++11 -I../logging arrays_6.cpp -o arrays_6
g++ -std=c++11 -I../logging arrays_7.cpp -o arrays_7
g++ -std=c++11 -DSIZE=5 -I../logging arrays_8.cpp -o arrays_8
g++ -std=c++11 -DSIZE=5 -I../logging arrays_9.cpp -o arrays_9
g++ -std=c++11 -I../logging arrays_10.cpp -o arrays_10
g++ -std=c++11 -I../logging arrays_11.cpp -o arrays_11
g++ -std=c++11 -I../logging arrays_12.cpp -o arrays_12
g++ -std=c++11 -I../logging arrays_13.cpp -o arrays_13
g++ -std=c++11 -I../logging arrays_14.cpp -o arrays_14
g++ -std=c++11 -I../logging arrays_15.cpp -o arrays_15
g++ -std=c++11 -I../logging arrays_16.cpp -o arrays_16
g++ -std=c++11 -I../logging arrays_17.cpp -o arrays_17

./arrays_1
./arrays_2
./arrays_3
./arrays_4
./arrays_5
./arrays_6
./arrays_7
./arrays_8
./arrays_9
./arrays_10
./arrays_11
./arrays_12
./arrays_13
./arrays_14
./arrays_15
./arrays_16
./arrays_17

rm ./arrays_1
rm ./arrays_2
rm ./arrays_3
rm ./arrays_4
rm ./arrays_5
rm ./arrays_6
rm ./arrays_7
rm ./arrays_8
rm ./arrays_9
rm ./arrays_10
rm ./arrays_11
rm ./arrays_12
rm ./arrays_13
rm ./arrays_14
rm ./arrays_15
rm ./arrays_16
rm ./arrays_17

