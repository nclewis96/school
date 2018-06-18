/*
 * @file ClientDriver.cpp 
 * 
 * Phillip J. Curtiss, Assistant Professor
 * Computer Science Department, Montana Tech
 * F15 CSCI232 - 
 */

// Our HeapInterface
#include "HeapInterface.h"
#include "ArrayMaxHeap.h"

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
ArrayMaxHeap<int> I1 = ArrayMaxHeap<int>();

I1.add(1);
I1.add(2);
I1.add(1);
I1.add(3);
I1.add(5);

I1.remove();
// Rest of the ClinetDriver will be provided later for testing
// Output end of report identifier
cout << endl << " - End of Output - " << endl;
// Terminate normally
return(0);
}

