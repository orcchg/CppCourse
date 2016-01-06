# http://habrahabr.ru/post/155201/

SHELL=/bin/bash
CC=g++
AR=ar
RANLIB=ranlib
CFLAGS=-std=c++11 -I../include

all: libprint.a

libprint.o:
	$(CC) $(CFLAGS) libprint.cpp -c -o libprint.o

libprint.a: libprint.o
	$(AR) rc $@ $^ && $(RANLIB) $@

clean:
	rm libprint.a libprint.o

