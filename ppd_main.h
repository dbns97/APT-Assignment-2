/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #2
 * Full Name        : Drew Nuttall-Smith
 * Student Number   : s3545039
 * Course Code      : COSC1076
 * Program Code     : BP096
 * Start up code provided by Paul Miller
 * Some codes are adopted here with permission by an anonymous author
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "ppd_stock.h"
#include "ppd_coin.h"
#include "ppd_shared.h"
#ifndef PPD_MAIN
#define PPD_MAIN
/**
 * @file ppd_main.h this file holds the rest of the application together.
 * From these header files, main() can call all functions refered to
 * in the header files included. You might also want to insert here
 * any functions for handling and validation of command line arguments
 **/

BOOLEAN get_params(struct ppd_system* system, int argc, char** argv);

#endif
