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

#include "ppd_menu.h"
/**
 * @file ppd_menu.c handles the initialised and management of the menu
 * array
 **/

/**
 * @param menu the menu item array to initialise
 **/
void init_menu( struct menu_item* menu) {
	/* Variables */
	int i;
	char menu_names[NUM_MENU_ITEMS][MENU_NAME_LEN + 1] = {
		"Display Items",
		"Purchase Items",
		"Save and Exit",
		"Add Item",
		"Remove Item",
		"Display Coins",
		"Reset Stock",
		"Reset Coins",
		"Abort Program"
	};
	menu_function menu_functions[NUM_MENU_ITEMS] = {
		&display_items,
		&purchase_item,
		&save_system,
		&add_item,
		&remove_item,
		&display_coins,
		&reset_stock,
		&reset_coins,
		NULL
	};

	for (i = 0; i < NUM_MENU_ITEMS; i++) {
		strcpy(menu[i].name, menu_names[i]);
		menu[i].function = menu_functions[i];
	}

}

void print_menu(struct menu_item* menu) {

	int i;

	printf("\nMain Menu:\n");

	for (i = 0; i < NUM_MENU_ITEMS; i++) {
		if (i == 3) printf("Administrator-Only Menu:\n");
		printf("%d.%s\n",(i + 1),menu[i].name);
	}

	printf("Select your option (1-9): ");

}

/**
 * @return a menu_function that defines how to perform the user's
 * selection
 **/
menu_function get_menu_choice(struct menu_item * menu) {

	/* Variables */
	char buffer[1 + EXTRACHARS];
	int bufferLength = 1 + EXTRACHARS;
	char *ptr = NULL;
	int selection;

	/* Get user input from stdin and check the buffer */
	fgets(buffer, bufferLength, stdin);
	if (buffer[0] == '\n') return NULL;
	if (checkBuffer(buffer, bufferLength) == FALSE) return NULL;

	/* Read value from buffer as number */
	selection = strtol(buffer, &ptr, 10);

	printf("\n");

	return menu[selection - 1].function;
	
}
