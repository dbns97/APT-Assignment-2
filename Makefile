########################################################################
# COSC1076 - Advanced Programming Techniques
# Semester 2 2014 Assignment #2
# Full Name        : Drew Nuttall-Smith
# Student Number   : s3545039
# Course Code      : COSC1076
# Program Code     : BP096
# Start up code provided by Paul Miller
########################################################################

SOURCES=ppd_main.c ppd_menu.c ppd_options.c ppd_utility.c ppd_stock.c \
ppd_coin.c
HEADERS=ppd_main.h ppd_menu.h ppd_options.h ppd_utility.h ppd_stock.h \
ppd_coin.h
OBJECTS=ppd_main.o ppd_menu.o ppd_options.o ppd_utility.o ppd_stock.o \
ppd_coin.o
README=ppd_readme
MAKEFILE=Makefile
CC=gcc
CFLAGS=-ansi -Wall -pedantic
FILENAME=ppd

all: $(OBJECTS)
	$(CC) $(CFLAGS) -lm -o $(FILENAME) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

g:
	$(CC) $(CFLAGS) -g -lm -o $(FILENAME) $(OBJECTS)

clean:
	rm $(FILENAME) $(OBJECTS)

archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) $(README) $(MAKEFILE)

