# http://habrahabr.ru/post/155201/

# @see http://stackoverflow.com/questions/10749058/building-and-linking-a-shared-library
# @see https://gist.github.com/xuhdev/1873316

SHELL=/bin/bash
CC=g++
CFLAGS=-std=c++11 -I../include -fPIC
LDFLAGS=-shared

all: libprint.so

libprint.o:
	$(CC) $(CFLAGS) libprint.cpp -c -o libprint.o

libprint.so: libprint.o
	$(CC) $(LDFLAGS) -Wl,-soname,$@ -o $@ $^

clean:
	rm libprint.so libprint.o

