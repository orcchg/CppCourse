# http://habrahabr.ru/post/155201/

SHELL=/bin/bash
SUBDIRS=advanced
CLEANDIRS=$(SUBDIRS:%=clean-%)
CC=g++
CFLAGS=-std=c++11 -I../include

all:
	$(CC) $(CFLAGS) containers_1.cpp -o containers_1
	$(CC) $(CFLAGS) containers_2.cpp -o containers_2
	$(CC) $(CFLAGS) containers_3.cpp -o containers_3
	$(CC) $(CFLAGS) containers_4.cpp -o containers_4
	$(CC) $(CFLAGS) containers_5.cpp -o containers_5
	$(CC) $(CFLAGS) containers_6.cpp -o containers_6
	$(CC) $(CFLAGS) containers_7.cpp -o containers_7
	$(CC) $(CFLAGS) containers_8.cpp -o containers_8
	$(CC) $(CFLAGS) containers_9.cpp -o containers_9
	$(MAKE) -C advanced

clean: $(CLEANDIRS)
$(CLEANDIRS): 
	$(MAKE) -C $(@:clean-%=%) clean
	rm containers_1 containers_2 containers_3 containers_4 containers_5 containers_6 containers_7 containers_8 containers_9

