/** @file io_functions.cpp
 *
 * Contains C++ functions for printing menus, reading input values, etc.
 * @author Braun
 * @date 1/12/14
 */

#include "io_functions.h"

using namespace std;

/**Prints main program menu
 * @pre  none
 * @post none
 */
void printMenu(){
  cout << "1) Print the size of graph" << endl;
  cout << "2) Check if an edge is in the graph" << endl;
  cout << "3) Insert an edge into the graph" << endl;
  cout << "4) Delete an edge from the graph" << endl;
  cout << "5) Retrieve an edge weight" << endl;
  cout << "6) Display the graph" << endl;
  cout << "7) Quit the program" << endl;
}

/**Reads, validates, and returns a positive integer
 * @pre  User has been prompted to enter an integer
 * @post none
 * @return nonnegative integer value
 */
int getInt(){
  int intValue = 0;
  string inputStr;
  do{
    getline(cin, inputStr);
    stringstream(inputStr) >> intValue;
    if(intValue < 0) cout << "ERROR - please enter a nonnegative integer> ";
  } while(intValue < 0);
  return intValue;
}

