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

#include "ppd_options.h"

/**
 * @file ppd_options.c this is where you need to implement the main
 * options for your program. You may however have the actual work done
 * in functions defined elsewhere.
 * @note if there is an error you should handle it within the function
 * and not simply return FALSE unless it is a fatal error for the
 * task at hand. You want people to use your software, afterall, and
 * badly behaving software doesn't get used.
 **/

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true as this particular function should never fail.
 **/
BOOLEAN display_items(struct ppd_system * system) {
	/* Variables */
	struct ppd_node* current_node = system->item_list->head;

	/* Print table headings */
	printf("ID    | Name                                     | Available | Price\n");
	printf("--------------------------------------------------------------------\n");

	/* Loop over nodes in list and print each stock item */
	while (current_node != NULL) {
		printf("%-*s | %-*s | %-*d | $%d.%02d\n",
			IDLEN,
			current_node->data->id,
			NAMELEN,
			current_node->data->name,
			9,
			current_node->data->on_hand,
			current_node->data->price.dollars,
			current_node->data->price.cents
		);

		current_node = current_node->next;
	}

	return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true when a purchase succeeds and false when it does not
 **/
BOOLEAN purchase_item(struct ppd_system * system) {
	/* Variables */
	char itemId[IDLEN + EXTRACHARS];
	int itemIdLen = IDLEN + EXTRACHARS;
	struct ppd_stock* item;
	int itemCost;
	char coinValue[IDLEN + EXTRACHARS];
	int coinValueLen = IDLEN + EXTRACHARS;
	char *ptr = NULL;
	int paid;
	int dollarsOwed;
	int centsOwed;
	int change;

	/* Prompt user to enter item choice */
	printf("Purchase Item\n");
	printf("-------------\n");
	printf("Please enter the id of the item you wish to purchase: ");

	/* Get user input from stdin and check the buffer */
	fgets(itemId, itemIdLen, stdin);
	if (checkBuffer(itemId, itemIdLen) == FALSE) {
		printf("Invalid item ID!\n\n");
		return purchase_item(system);
	}

	/* Find the item that the user selected and check if it exists */
	item = find_list_item(system->item_list, itemId);
	if (item == NULL) {
		printf("That item does not exist!\n");
		printf("Please enter a valid item ID:\n\n");
		return purchase_item(system);
	} else if (item->on_hand == 0) {
		printf("Sorry, that item is out of stock!\n\n");
		return FALSE;
	}

	printf("You have selected \"%s  %s\". This will cost you $%d.%02d.\n", item->name, item->desc, item->price.dollars, item->price.cents);
	printf("Please hand over the money – type in the value of each note/coin in cents.\n");
	printf("Press enter on a new and empty line to cancel this purchase:\n");

	itemCost = item->price.cents + (100 * item->price.dollars);
	paid = 0;
	dollarsOwed = item->price.dollars;
	centsOwed = item->price.cents;

	/* Receive coins from user until they have paid the full amount or cancelled the transaction */
	while (paid < itemCost) {
		printf("You still need to give us $%d.%02d: ", dollarsOwed, centsOwed);

		fgets(coinValue, coinValueLen, stdin);
		if (coinValue[0] == '\n') break;
		if (checkBuffer(coinValue, coinValueLen) == FALSE) {
			printf("Please enter valid value!\n");
			continue;
		}

		paid += strtol(coinValue, &ptr, 10);
		dollarsOwed -= floor(strtol(coinValue, &ptr, 10) / 100);
		centsOwed -= strtol(coinValue, &ptr, 10) % 100;

	}

	/* Remove one from the qty on hand */
	item->on_hand--;
	printf("Thank you. Here is your %s", item->name);
	if (paid > itemCost) {
		change = paid - itemCost;
		printf(", and your change of $%f.%02d", floor(change / 100), (change % 100));
	}
	printf(".\n");
	printf("Please come back soon.\n");

	return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true when a save succeeds and false when it does not
 **/
BOOLEAN save_system(struct ppd_system * system)
{
	/* Variables */
	int i;
	FILE* fp;
	struct ppd_node* current = system->item_list->head;

	/* Open file and write each stock item to it */
	fp = fopen(system->stock_file_name, "w");
	for (i = 0; i < system->item_list->count; i++) {
		fprintf(fp, "%s|%s|%s|%d.%02d|%d\n",
			current->data->id,
			current->data->name,
			current->data->desc,
			current->data->price.dollars,
			current->data->price.cents,
			current->data->on_hand
		);
		current = current->next;
	}

	fclose(fp);
	system_free(system);
	exit(0);

    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true when adding an item succeeds and false when it does not
 **/
BOOLEAN add_item(struct ppd_system * system)
{
	/* Variables */
	struct ppd_stock stock;
	char buffer[4 + EXTRACHARS];
	int bufferLen = 4 + EXTRACHARS;
	char *ptr = NULL;
	char delim[2] = ".";
	char* token;

	system->item_list->count++;
	sprintf(stock.id, "I%04d", system->item_list->count);

	printf("This new meal item will have the Item id of %s\n", stock.id);

	/* Get item name */
	printf("Enter the item name: ");
	fgets(stock.name, (NAMELEN + EXTRACHARS), stdin);
	if (checkBuffer(stock.name, (NAMELEN + EXTRACHARS)) == FALSE) {
		printf("\nInvalid input!\n\n");
		return FALSE;
	}

	/* Get item description */
	printf("Enter the item description: ");
	fgets(stock.desc, (DESCLEN + EXTRACHARS), stdin);
	if (checkBuffer(stock.desc, (DESCLEN + EXTRACHARS)) == FALSE) {
		printf("\nInvalid input!\n");
		return FALSE;
	}

	/* Get item price */
	printf("Enter the price for this item: ");
	fgets(buffer, bufferLen, stdin);
	if (checkBuffer(buffer, bufferLen) == FALSE) {
		printf("\nInvalid input!\n");
		return FALSE;
	}

	token = strtok(buffer, delim);
	stock.price.dollars = strtol(token, &ptr, 10);
	token = strtok(NULL, delim);
	stock.price.cents = strtol(token, &ptr, 10);

	/* Set initial stock level */
	stock.on_hand = DEFAULT_STOCK_LEVEL;

	printf("This item \"%s - %s\" has now been added to the menu.\n", stock.name, stock.desc);

	/* Add to list */
    return add_list_item(system->item_list, &stock);
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true when removing an item succeeds and false when it does not
 **/
BOOLEAN remove_item(struct ppd_system * system)
{
    /*
     * Please delete this default return value once this function has
     * been implemented. Please note that it is convention that until
     * a function has been implemented it should return FALSE
     */
    return FALSE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true as this function cannot fail.
 **/
BOOLEAN reset_stock(struct ppd_system * system)
{
    /*
     * Please delete this default return value once this function has
     * been implemented. Please note that it is convention that until
     * a function has been implemented it should return FALSE
     */
    return FALSE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true as this function cannot fail.
 **/
BOOLEAN reset_coins(struct ppd_system * system)
{
    /*
     * Please delete this default return value once this function has
     * been implemented. Please note that it is convention that until
     * a function has been implemented it should return FALSE
     */
    return FALSE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains
 * all the information for managing the system.
 * @return true as this function cannot fail
 **/
BOOLEAN display_coins(struct ppd_system * system)
{
    /*
     * Please delete this default return value once this function has
     * been implemented. Please note that it is convention that until
     * a function has been implemented it should return FALSE
     */
    return FALSE;
}

BOOLEAN abort_program(struct ppd_system * system) {
	system_free(system);
	exit(0);
}
