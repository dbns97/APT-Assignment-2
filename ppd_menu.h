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
#include "ppd_utility.h"
#include "ppd_options.h"

/**
 * @file ppd_menu.h defines the @ref menu_item type and the init_menu
 * function which you need to call to initialise it
 **/
#ifndef MENU_H
#define MENU_H
/**
 * The maximum length of a menu item's text
 **/
#define MENU_NAME_LEN 50

/**
 * The number of options displayed in the menu
 **/
#define NUM_MENU_ITEMS 9

/* represents a function that can be selected from the list of
 * menu_functions - creates a new type called a menu_function
 */
typedef BOOLEAN (*menu_function)(struct ppd_system*);

/**
 * represents a menu item to be displayed and executed in the program
 **/
struct menu_item
{
    /**
     * the text to be displayed in the menu
     **/
    char name[MENU_NAME_LEN + 1];
    /**
     * pointer to the function to be called when this item is selected
     **/
    menu_function function;
};

/**
 * Initialises the menu array with names and function pointers
 **/
void init_menu( struct menu_item*);

/**
 * Prints the menu and prompts user to select an option 
 **/
void print_menu(struct menu_item*);

/**
 * Get the user's input and return the appropriate function pointer
 **/
menu_function get_menu_choice(struct menu_item*);
#endif
