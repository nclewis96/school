/** @file io_functions.cpp
 *
 * Contains C++ functions for printing menus, reading input values, etc.
 * @author Braun
 * @date 9/2/14
 */

#include "io_functions.h"

using namespace std;

/**Prints main program menu
 * @pre  none
 * @post none
 */
void printMenu(){
   cout << "1) Print the size of the bag" << endl;
   cout << "2) Add an item into the bag" << endl;
   cout << "3) Remove an item from the bag" << endl;
   cout << "4) Check for an item in the bag" << endl;
   cout << "5) Combine 2 bags into one bag" << endl;
   cout << "6) Intersect 2 bags" << endl;
   cout << "7) Display the bag" << endl;
   cout << "8) Quit the program" << endl;
}

/**Reads, validates, and returns a positive integer
 * @pre  User has been prompted to enter an integer
 * @post none
 * @return positive integer value
 */
int getInt(){
  int intValue = 0;
  string inputStr;
  do{
    getline(cin, inputStr);
    stringstream(inputStr) >> intValue;
    if(intValue < 1) cout << "ERROR - please enter a positive integer> ";
  } while(intValue < 1);
  return intValue;
}

/**
  * Prompts for a bag item and returns it to caller
  * @return bag item
  * @remarks Accepts strings with spaces
  */
string getItem()
{
  string item;
  cout << "Enter the bag item> ";
  getline(cin, item);
  return item;
}

