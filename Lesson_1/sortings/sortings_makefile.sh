#!/bin/bash

g++ -std=c++11 -I../logging insertion_sort.cpp -o insertion_sort
g++ -std=c++11 -I../logging insertion_sort_bug.cpp -o insertion_sort_bug
g++ -std=c++11 -I../logging merge_sort.cpp -o merge_sort
g++ -std=c++11 -I../logging quick_sort.cpp -o quick_sort
g++ -std=c++11 -DSIZE=100 -I../logging standard_sort_1.cpp -o standard_sort_1
g++ -std=c++11 -I../logging standard_sort_2.cpp -o standard_sort_2
g++ -std=c++11 -I../logging standard_sort_3.cpp -o standard_sort_3

./insertion_sort
./insertion_sort_bug
./merge_sort
./quick_sort
./standard_sort_1
./standard_sort_2
./standard_sort_3

rm ./insertion_sort
rm ./insertion_sort_bug
rm ./merge_sort
rm ./quick_sort
rm ./standard_sort_1
rm ./standard_sort_2
rm ./standard_sort_3

