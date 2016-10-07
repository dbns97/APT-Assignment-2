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
 * This function initialises data structures, loads data, displays
 * the menu and executes the user's selection
 **/
int main(int argc, char **argv) {

	struct menu_item menu[NUM_MENU_ITEMS];

	/* represents the data structures to manage the system */
	struct ppd_system system;

	/* init the system */
	system_init(&system);

	/* load data */
	get_params(&system, argc, argv);
	load_stock(&system, system.stock_file_name);

	/* initialise the menu system */
	init_menu(menu);

	/* loop, asking for options from the menu */
	while (TRUE) {

		menu_function funcPtr;

		print_menu(menu);

		/* Get the pointer to the function to execute and check it exists */
		funcPtr = get_menu_choice(menu);
		if (funcPtr == NULL) {
			printf("\nInvalid selection!\n");
			continue;
		}

		/* Execute function and check return value */
		if(!(*funcPtr)(&system)) {
			printf("Operation failed!");
		}

	}

	return EXIT_SUCCESS;
}

/**
 * This function gets the command line arguments and
 * saves them in the system
 **/
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
