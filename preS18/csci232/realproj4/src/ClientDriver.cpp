/*
 * @file ClientDriver.cpp 
 * 
 * Phillip J. Curtiss, Assistant Professor
 * Computer Science Department, Montana Tech
 * F15 CSCI232 - 
 */

// Our SortedListInterface
#include "SortedListInterface.h"
#include "SortedListADT.h"

// Requried to be able to write to output 
#include <iostream>

// Search the std namespace when reference is not found
using namespace std;

/*
 * Main driver program - entry pointer
 */
int main()
{
// Create two integer based SortedListADT lists
SortedListADT<int> I1 = SortedListADT<int>();

// Create a string based SortedListADT Lists
SortedListADT<string> S1 = SortedListADT<string>();

I1.insertSorted(1);
I1.insertSorted(2);
I1.insertSorted(1);
I1.insertSorted(3);
I1.insertSorted(5);

S1.insertSorted("apple");
S1.insertSorted("orange");
S1.insertSorted("banana");
S1.insertSorted("apple");
S1.insertSorted("the");
SortedListADT<string> S2 = SortedListADT<string>(S1);
S1.removeSorted("the");
cout << S1 << endl;
cout << S2 << endl;
// Rest of the ClinetDriver will be provided later for testing
// Output end of report identifier
cout << endl << " - End of Output - " << endl;
// Terminate normally
return(0);
}

