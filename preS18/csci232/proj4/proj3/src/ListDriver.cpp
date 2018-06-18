/** @file ListDriver.cpp
 * List Main Driver - use to generate Santa List
 *                                
 * @author  Phil Curtiss 
 * @version 1.0
 * @date 10/14/15
 **********************************************************/

//-----------------------
// Using statements
//-----------------------
using namespace std;
 
//-----------------------
// C++ includes
//-----------------------
#include <iostream>
#include <fstream>
#include <string>


//-----------------------
// Application includes
//-----------------------
#include "ListInterface.h"
#include "ListADT.h"
#include "listItems.h"

/** List Driver - use to help Santa with his Lists
 **********************************************************/
int main(int argc, char *argv[])
{
  // Instantiate a ListADT object
  
  ListInterface<string> *naughtyList = new ListADT<string>();
  ListInterface<string> *niceList = new ListADT<string>();

  // Check to make sure we are passed one or more filenames to
  // process for Santa - insert into our ListADT() in such a way
  // that the entries are ordered and grouped.
  if (argc < 3){
	  cout << "Usage " << "foo" << ": <naughty filename> <nice filename>" << endl;
	  return(1);
  }
  
  // We now have commmand line arguments to process, so let's 
  // get to it and populate santa's lists
  if (naughtyList->loadList(argv[1]) == false)
	  cout << "Problem reading entries from naughty list: " << argv[1] << endl;
  
  if (niceList->loadList(argv[2]) == false)
	  cout << "Problem reading entries from nice list: " << argv[2] << endl;
  
  // If the list has some items present, then let's display this 
  // list for Santa
  cout << "Your sorted nice list of boys and girls to visit:" << endl;
  if (niceList->isEmpty() == false)
	niceList->displayList();
  else
	cout << "Couldn't find any nice little borys and girls. ;-(" << endl;

  // If the list has some items present, then let's display this
  // list for Santa
  cout << "Your sorted naughty list of boys and girls to visit:" << endl;
  if (naughtyList->isEmpty() == false)
    naughtyList->displayList();
  else 
	cout << "Couldn't find any naughty little boys and girls. :-)" << endl;
  
  return 0;            //Exit program
}//main()
