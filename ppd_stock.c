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
#include "ppd_stock.h"

 /**
  * @file ppd_stock.c this is the file where you will implement the
  * interface functions for managing the stock list.
  **/

/* Initialise the list of stock items */
struct ppd_list* list_init() {
	/* Allocate dynamic memory for list */
	struct ppd_list* list = malloc(sizeof(struct ppd_list));

	if (list != NULL) {
		list->head = NULL;
		list->count = 0;
	}

	return list;
}

/* Add a stock item to the system's list */
BOOLEAN add_list_item(struct ppd_list* list, struct ppd_stock* stock) {

	/* Variables */
	struct ppd_node* new_node = malloc(sizeof(*new_node)); /* New node struct to be added to list */
	struct ppd_node* current_node = list->head; /* Current node in list being compared to new_node */
	struct ppd_node* prev_node = NULL; /* Previous node in list that was compared to new_node */

	if (new_node == NULL) return FALSE;

	/* Initialise new_node's values */
	new_node->data = malloc(sizeof(*new_node->data));

	if (new_node->data == NULL) {
		free(new_node);
		return FALSE;
	}

	*new_node->data = *stock;
	/*new_node->next = malloc(sizeof(*new_node->next));

	if (new_node->next == NULL) {
		free(new_node->data);
		free(new_node);
		return FALSE;
	}*/
	new_node->next = NULL;

	/* Loop over list and compare new_node's name to each existing node's name */
	while (current_node != NULL) {
		if (strcmp(new_node->data->name, current_node->data->name) < 0) {
			break;
		} else {
			prev_node = current_node;
			current_node = current_node->next;
		}
	}

	if (list->head == NULL) { /* Adding node to empty list */
		list->head = new_node;
	} else if (prev_node == NULL) { /* Adding node to beginning of list */
		new_node->next = list->head;
		list->head = new_node;
	} else { /* Adding node to middle or end of list */
		prev_node->next = new_node;
		new_node->next = current_node;
	}
	list->count++;

	return TRUE;

}

struct ppd_stock* find_list_item(struct ppd_list* list, char* selectedId) {

	/* Variables */
	int i;
	struct ppd_node* current = list->head;

	for (i = 0; i < list->count; i++) {
		if (strcmp(current->data->id, selectedId) == 0) {
			return current->data;
		}
		current = current->next;
	}

	return NULL;
}



