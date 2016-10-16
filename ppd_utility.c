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

BOOLEAN checkBuffer(char buffer[], int bufferLength) {

	/*Variables*/
	int i;

	/* Check every character in the buffer */
	for (i = 0; i < bufferLength; i++) {
		/* Replace any newline characters with a null character */
		if (buffer[i] == '\n') {
			buffer[i] = '\0';
			break;
		/* If the last character is not a newline character there has been an overflow */
		} else if (i == bufferLength - 1) {
			read_rest_of_line();
			return FALSE;
		}
	}

	return TRUE;

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
	char line[IDLEN + 1 + NAMELEN + 1 + DESCLEN + 1 + 4 + 1 + 2 + 1]; /* Char array with length of max line length */
	const char delim[3] = "|.";
	char* token;
	struct ppd_stock stock;
	BOOLEAN fileEmpty = TRUE;

	fp = fopen(filename, "r");
	if (fp == NULL) return FALSE;

	/* Read line-by-line until the end of the file */
	while (fgets(line, (sizeof(line)/sizeof(*line)), fp) != NULL) {
		fileEmpty = FALSE;

		/* Assign values to the stock from the line in the file */
		/* Get item id */
		token = strtok(line, delim);
		if (token == NULL) {
			printf("Invalid ID in stock file!\n");
			return FALSE;
		} else if ((sizeof token / sizeof *token) > (IDLEN + 3)) {
			printf("Length of ID: %lu\n", (sizeof token / sizeof *token));
			printf("ID in file is too long!\n");
			return FALSE;
		}
		strcpy(stock.id, token);

		/* Get item name */
		token = strtok(NULL, delim);
		if (token == NULL) {
			printf("Invalid name in stock file!\n");
			return FALSE;
		} else if ((sizeof token / sizeof *token) > (NAMELEN + 1)) {
			printf("Name in file is too long!\n");
			return FALSE;
		}
		strcpy(stock.name, token);

		/* Get item description */
		token = strtok(NULL, delim);
		if (token == NULL) {
			printf("Invalid description in stock file!\n");
			return FALSE;
		} else if ((sizeof token / sizeof *token) > (DESCLEN + 1)) {
			printf("Description in file is too long!\n");
			return FALSE;
		}
		strcpy(stock.desc, token);

		/* Get item price, dollars component */
		token = strtok(NULL, delim);
		if (token == NULL) {
			printf("Invalid price (dollars) in stock file!\n");
			return FALSE;
		} else if (strtol(token, NULL, 10) == 0 && token[0] != '0') {
			printf("Invalid price (dollars) in stock file!\n");
			return FALSE;
		} else if (strtol(token, NULL, 10) > MAX_DOLLARS || strtol(token, NULL, 10) < 0) {
			printf("Invalid price (dollars) in stock file!\n");
			return FALSE;
		}
		stock.price.dollars = strtol(token, NULL, 10);

		/* Get item price, cents component */
		token = strtok(NULL, delim);
		if (token == NULL) {
			printf("Invalid price (cents) in stock file!\n");
			return FALSE;
		} else if (strtol(token, NULL, 10) == 0 && token[0] != '0') {
			printf("Invalid price (cents) in stock file!\n");
			return FALSE;
		} else if (strtol(token, NULL, 10) > MAX_CENTS || strtol(token, NULL, 10) < 0) {
			printf("Invalid price (cents) in stock file!\n");
			return FALSE;
		}
		stock.price.cents = strtol(token, NULL, 10);

		/* Get item count */
		token = strtok(NULL, delim);
		if (token == NULL) {
			printf("Invalid count in stock file!\n");
			return FALSE;
		} else if (strtol(token, NULL, 10) == 0 && token[0] != '0') {
			printf("Invalid count in stock file!\n");
			return FALSE;
		} else if (strtol(token, NULL, 10) > MAX_STOCK_LEVEL || strtol(token, NULL, 10) < 0) {
			printf("Invalid count in stock file!\n");
			return FALSE;
		}
		stock.on_hand = strtol(token, NULL, 10);

		token = strtok(NULL, delim);
		if (token != NULL) {
			printf("Extra tokens in stock file!\n");
			return FALSE;
		}

		/* Add a node to the system's list */
		add_list_item(system->item_list, &stock);

	}

	/* Check if file is empty */
	if (fileEmpty) {
		printf("Stock file empty!\n");
		return TRUE;
	}

	fclose(fp);

	return TRUE;
}

/**
 * loads the contents of the coins file into the system. This needs to
 * be implemented as part 1 of requirement 18.
 **/
BOOLEAN load_coins(struct ppd_system * system, const char * filename)
{
	/* Variables */
	FILE* fp;
	char line[4 + 1 + 2 + 1]; /* Char array with length of max line length */
	int lineCount = 0;
	char* token;
	char* ptr;
	struct coin coins[NUM_DENOMS];
	int denominations[NUM_DENOMS] = {1000,500,200,100,50,20,10,5};
	int denomCount;
	int i;

	/* Initialise coin denominations */
	for (i = 0; i < NUM_DENOMS; i++) {
		coins[i].denom = i;
	}

	fp = fopen(filename, "r");
	if (fp == NULL) return FALSE;

	/* Read line-by-line until the end of the file */
	while (fgets(line, (sizeof(line)/sizeof(*line)), fp) != NULL) {

		/* Get and check denomination value from line */
		token = strtok(line, COIN_DELIM);
		if (token == NULL) {
			printf("Invalid line in coin file!");
			return FALSE;
		}

		/* Find denomination value in denominations array */
		for (i = 0; i < NUM_DENOMS; i++) {
			/* Denomination was found */
			if (strtol(token, &ptr, 10) == denominations[i]) {
				/* Get and check count from line */
				token = strtok(NULL, COIN_DELIM);
				if (token == NULL) {
					printf("Invalid line in coin file!");
					return FALSE;
				}

				/* Convert to integer and check if it was a valid number */
				denomCount = strtol(token, &ptr, 10);
				if (denomCount == 0 && token[0] != '0') {
					printf("Invalid count in coin file!");
					return FALSE;
				}

				coins[i].count = denomCount;

				break;
			} else {
				/* denomination was not found, therefore file is invalid */
				if (i == (NUM_DENOMS - 1)) {
					printf("Invalid denomination in coin file!");
					return FALSE;
				}
			}
		}

		/* Make sure there is nothing left on the line */
		if (strtok(NULL, COIN_DELIM) != NULL) {
			printf("Invalid line in coin file!");
			return FALSE;
		}

		memcpy(system->cash_register, coins, sizeof(system->cash_register));

		lineCount++;

	}

	/* Check if the correct number of denominations was provided */
	if (lineCount != NUM_DENOMS) {
		printf("Wrong number of denominations in coin file!");
		return FALSE;
	}

	fclose(fp);

	return TRUE;
}

/**
 * @param system a pointer to a @ref ppd_system struct that holds all
 * the data for the system we are creating
 **/
void system_free(struct ppd_system * system)
{
	/* Variables */
	struct ppd_node* current = system->item_list->head;

	while (current != NULL) {
		struct ppd_node* temp = current;
		current = current->next;

		free(temp->data);
		free(temp);
	}

	free(system->item_list);

}
