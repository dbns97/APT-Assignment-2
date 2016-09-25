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

#include "ppd_utility.h"
/**
 * @file ppd_utility.c contains implementations of important functions for
 * the system. If you are not sure where to implement a new function,
 * here is probably a good spot.
 **/

void read_rest_of_line(void)
{
	int ch;
	/* keep retrieving characters from stdin until we
	 * are at the end of the buffer
	 */
	while(ch = getc(stdin), ch!='\n' && ch != EOF)
		;
	/* reset error flags on stdin */
	clearerr(stdin);
}

/**
 * @param system a pointer to a @ref ppd_system struct that holds all
 * the data for the system we are creating
 **/
BOOLEAN system_init(struct ppd_system * system)
{
	/* Initialise file name variables to empty strings */
	system->stock_file_name = "";
	system->coin_file_name = "";
	system->item_list = list_init();

	if (system->item_list == NULL) {
		return FALSE;
	} else {
		return TRUE;
	}

}

/**
 * loads the stock file's data into the system. This needs to be
 * implemented as part of requirement 2 of the assignment specification.
 **/
BOOLEAN load_stock(struct ppd_system * system, const char * filename)
{
	/* Variables */
	FILE* fp;
	char line[IDLEN + 1 + NAMELEN + 1 + DESCLEN + 4 + 1 + 2 + 1]; /* Char array with length of max line length */
	const char delim[3] = "|.";
	struct ppd_stock stock;

	fp = fopen(filename, "r");
	if (fp == NULL) return FALSE;

	/* Read line-by-line until the end of the file */
	while (fgets(line, (sizeof(line)/sizeof(*line)), fp) != NULL) {
		/* Create new stock struct */
		/*stock_init(&stock);*/

		/* Assign values to the stock from the line in the file */
		strcpy(stock.id, strtok(line, delim));
		strcpy(stock.name, strtok(NULL, delim));
		strcpy(stock.desc, strtok(NULL, delim));
		stock.price.dollars = strtol(strtok(NULL, delim), NULL, 10);
		stock.price.cents = strtol(strtok(NULL, delim), NULL, 10);
		stock.on_hand = strtol(strtok(NULL, delim), NULL, 10);

		/*
		printf("----------\n");
		printf("%s\n", stock.id);
		printf("%s\n", stock.name);
		printf("%s\n", stock.desc);
		printf("%d.", stock.price.dollars);
		printf("%d\n", stock.price.cents);
		printf("%d\n", stock.on_hand);
		printf("----------\n");
		*/

		/* Add a node to the system's list */
		add_list_item(system->item_list, &stock);

	}

	/*
	 * Please delete this default return value once this function has
	 * been implemented. Please note that it is convention that until
	 * a function has been implemented it should return FALSE
	 */
	return FALSE;
}

/**
 * loads the contents of the coins file into the system. This needs to
 * be implemented as part 1 of requirement 18.
 **/
BOOLEAN load_coins(struct ppd_system * system, const char * filename)
{
	/*
	 * Please delete this default return value once this function has
	 * been implemented. Please note that it is convention that until
	 * a function has been implemented it should return FALSE
	 */
	return FALSE;

}

/**
 * @param system a pointer to a @ref ppd_system struct that holds all
 * the data for the system we are creating
 **/
void system_free(struct ppd_system * system)
{

}
