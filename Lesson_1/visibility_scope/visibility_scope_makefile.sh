#!/bin/bash

g++ -std=c++11 visibility_scope_1.cpp -o visibility_scope_1
g++ -std=c++11 visibility_scope_2.cpp -o visibility_scope_2
g++ -std=c++11 visibility_scope_3.cpp -o visibility_scope_3
g++ -std=c++11 visibility_scope_4.cpp -o visibility_scope_4
g++ -std=c++11 visibility_scope_5.cpp -o visibility_scope_5
g++ -std=c++11 visibility_scope_6.cpp -o visibility_scope_6
g++ -std=c++11 visibility_scope_7.cpp -o visibility_scope_7
g++ -std=c++11 visibility_scope_quiz.cpp -o visibility_scope_quiz

./visibility_scope_1
./visibility_scope_2
./visibility_scope_3
./visibility_scope_4
./visibility_scope_5
./visibility_scope_6
./visibility_scope_7
./visibility_scope_quiz

