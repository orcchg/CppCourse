# http://habrahabr.ru/post/155201/

SHELL=/bin/bash
SUBDIRS=advanced
CLEANDIRS=$(SUBDIRS:%=clean-%)
CC=g++
CFLAGS=-std=c++11 -I../include

all:
	$(CC) $(CFLAGS) templates_0.cpp -o templates_0
	$(CC) $(CFLAGS) templates_0_1.cpp -o templates_0_1
	$(CC) $(CFLAGS) templates_0_2.cpp -o templates_0_2
	$(CC) $(CFLAGS) templates_1.cpp -o templates_1
	$(CC) $(CFLAGS) templates_2.cpp -o templates_2
	$(CC) $(CFLAGS) templates_3.cpp -o templates_3
	$(CC) $(CFLAGS) templates_4.cpp -o templates_4
	$(CC) $(CFLAGS) class_templates_0.cpp -o class_templates_0
	$(CC) $(CFLAGS) class_templates_1.cpp -o class_templates_1
	$(MAKE) -C advanced

clean: $(CLEANDIRS)
$(CLEANDIRS): 
	$(MAKE) -C $(@:clean-%=%) clean
	rm templates_0 templates_0_1 templates_0_2 templates_1 templates_2 templates_3 templates_4 class_templates_0 class_templates_1

