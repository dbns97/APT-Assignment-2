/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #2
 * Full Name        : Drew Nuttall-Smith
 * Student Number   : s3545039
 * Course Code      : COSC1076
 * Program Code     : BP096
 * Start up code provided by Paul Miller
 * Some codes are adopted here with permission by an anonymous author
 ***********************************************************************/

#include "ppd_main.h"
#include "ppd_menu.h"
#include "ppd_options.h"
#include "ppd_utility.h"

/**
 * @file ppd_main.c contains the main function implementation and any
 * helper functions for main such as a display_usage() function.
 **/

/**
 * manages the running of the program, initialises data structures, loads
 * data and handles the processing of options. The bulk of this function
 * should simply be calling other functions to get the job done.
 **/
int main(int argc, char **argv) {

	/*struct menu_item menu[NUM_MENU_ITEMS];*/

	/* validate command line arguments */

	/* represents the data structures to manage the system */
	struct ppd_system system;

	/* init the system */
	system_init(&system);

	/* load data */
	get_params(&system, argc, argv);
	load_stock(&system, system.stock_file_name);

	/* --------------- START TESTING --------------- */
	display_items(&system);
	/* ---------------- END TESTING ---------------- */

	/* test if everything has been initialised correctly */

	/* initialise the menu system */
	/*init_menu(menu);*/

	/* loop, asking for options from the menu */
	/*while (TRUE) {

		Variables
		int i;

		iterate over all elements of array "menu"
		for (i = 0; i < (sizeof (menu) / sizeof *(menu)); i++) {
			printf("%d.%s",i,menu[i]);
		}

	}*/

	/* run each option selected */

	/* until the user quits */

	/* make sure you always free all memory and close all files
	 * before you exit the program
	 */

	return EXIT_SUCCESS;
}

BOOLEAN get_params(struct ppd_system* system, int argc, char** argv) {

	if (argc > 1) system->stock_file_name = argv[1];
	if (argc > 2) system->coin_file_name = argv[2];

	if (system->stock_file_name == NULL) {
		return FALSE;
	/*} else if (system->coin_file_name == NULL) {
		return FALSE;*/
	} else {
		return TRUE;
	}

}
