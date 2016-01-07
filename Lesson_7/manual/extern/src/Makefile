# http://habrahabr.ru/post/155201/

# note the order of $(LIBS) - @see http://www.lurklurk.org/linkers/linkers.html

SHELL=/bin/bash
CC=g++
CFLAGS=-std=c++11 -I../include
LIBS=-ldl

all:
	$(CC) $(CFLAGS) main_2.cpp symbol_table.cpp -o main_2 $(LIBS)

clean:
	rm main_2

