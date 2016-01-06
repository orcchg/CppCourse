# http://habrahabr.ru/post/155201/

# note the order of $(LIBS) - @see http://www.lurklurk.org/linkers/linkers.html

SHELL=/bin/bash
CC=g++
CFLAGS=-std=c++11 -I../include
LIBS=-lprint
LDFLAGS=-L../lib/

all:
	$(CC) $(CFLAGS) $(LDFLAGS) main_1.cpp -o main_1 $(LIBS)

clean:
	rm main_1

