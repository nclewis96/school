/** @file io_functions.h
 *
 * Contains C++ functions for printing menus, reading input values, etc.
 * @author Braun
 * @date 9/16/13
 */

#ifndef IO_FUNCTIONS_H
#define IO_FUNCTIONS_H
#include <iostream>
#include <sstream>

using namespace std;

/**Prints main program menu
 * @pre  none
 * @post none
 */
void printMenu();

/**Reads and returns an integer
 * @pre  User has been prompted to enter an integer
 * @post none
 * @return integer value
 */
int getInt();

/**
  * Prompts for a list item and returns it to caller
  * @return list item
  * @remarks Accepts strings with spaces
  */
string getItem();

#endif
