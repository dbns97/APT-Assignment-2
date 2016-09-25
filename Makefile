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
README=ppd_readme
MAKEFILE=Makefile
CC=gcc
CFLAGS=-ansi -Wall -pedantic
FILENAME=ppd

########################################################################
# Move this target to the end of the Makefile to zip up your code 
# when submitting. Do not submit your .dat files, or directories. 
# We only want the files that are part of your implementation.
########################################################################

make:
	$(CC) $(CFLAGS) $(SOURCES) -o $(FILENAME)

g:
	$(CC) $(CFLAGS) -g $(SOURCES) -o $(FILENAME)

clean: $(FILENAME)
	rm $(FILENAME) 

archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) $(README) $(MAKEFILE)

