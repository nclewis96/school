/** @file BagDriver.cpp
 * Bag Driver - use to test Bag class methods and 
 *  functions that are independent from the Bag class.
 *  Bags 1 & 2 are used trough, bag 0 is extra for testing
 *                                
 * @author  Jeff Braun             
 * @version 0.9
 * @date 9/2/14
 **********************************************************/

//-----------------------
// C++ includes
//-----------------------
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//-----------------------
// Application includes
//-----------------------
#include "Bag.h"
#include "io_functions.h"

//-----------------------
// Using statements
//-----------------------
using namespace std;

//----------------------
// Functions Prototypes
//----------------------
int getBagNum();                 //prompts user for bag number
void processOption(char& c, Bag<string> bags[]);  //processes menu input option
void displayBag(Bag<string>& bag);   //display the bag's entire contents
void restoreBag(Bag<string>& bag);   //prompts for filename that contains items
void saveBag(Bag<string>& bag);   //prompts for filename to store items into

/** Bag Driver - use to test Bag class methods and 
 * bag functions that are independent from the Bag class.
 **********************************************************/
int main()
{
  int bagNum;              //The bag number to use
  Bag<string> bag[3];     // bags to test, bag 0 used for intersection/union
  string restoreBagFlg;  // holds response to restore bag from a file
  string menuOption;  	// holds menu option input from user

//Opening Message
  cout<< "Bag Driver - Tests the Bag class using two bags" << endl;

//Restore the bag from a file
  cout<< "----------------------------------" << endl; 
  cout<< "Would you like to restore a bag from a file? (Y/N) ";
   
//Read user input - use a string to accept all inputs
  getline(cin, restoreBagFlg);
  bagNum = getBagNum();
  if(restoreBagFlg[0] == 'Y' || restoreBagFlg[0] == 'y'){ 
    restoreBag(bag[bagNum]);            // opens/reads file into aBag
  }

//Menu driven part of main program
//Initial menu display and loop to process menu option
  printMenu();
  do {
    cout << "\nEnter menu selection (0 for menu): ";
    getline(cin, menuOption);    //Use a string in case user enters chars
    processOption(menuOption[0], bag);
  }while(menuOption[0] != '8');
   
  return 0;            //Exit program
}//main()


//---------------------------
// Local function definitions
//---------------------------

/**Reads, validates, and returns a 1 or 2
 * @pre  none
 * @post none
 * @return 1 or 2
 */
int getBagNum()
{
  int bagNum=0;  
  while(bagNum != 1 && bagNum != 2)
  {
    cout << "Which bag (1 or 2)? ";
    bagNum = getInt();
  }
  return bagNum;
} //getBagNum()

/**
 * Displays the entire content of the bag
 * @param[in] bag to display
 * @remarks If bag is empty, prints empty bag message.
 */
void displayBag(Bag<string>& bag) 
{
  string item;
  vector<string> bagVector = bag.toVector();

  if(bagVector.size() > 0)
  {
    cout << "The bag contains: " << endl;
    for(unsigned int i=0; i<bagVector.size(); i++){
      cout << bagVector[i] << ", ";
    }
    cout<<endl;
  }
  else
  {
    cout << "The bag is empty." << endl;
  }
}


/**
  * Process input menu option character from user.
  * @param[in] menuChar menu option character
  * @param[in,out] bag the bag to be modified
  */
void processOption(char &menuChar, Bag<string> bag[])
{
  int bagNum;
  string item;
  string saveBagFlg;

   switch (menuChar)
   {
    case '0':               // Display menu options
       printMenu();
       break;

    case '1':               // Output size of the bag
       cout << "\nBag Size is: " << bag[getBagNum()].getCurrentSize() << endl;
       break;

    case '2':               // Add items to the bag 
       cout << "Add Item:" << endl;
       item = getItem();
       bagNum = getBagNum();
       if(bag[bagNum].add(item))
       {
         cout << item << " was successfully added to bag " << bagNum << endl;
       }
       else
       {
         cout << item << " was not added to the bag." << endl;
       }
       break;

	case '3':				// Remove items from the bag
		cout << "Remove item: " << endl;
		item = getItem();
		bagNum = getBagNum();
		if (bag[bagNum].add(item)) {
			cout << "The item was successfully removed from bag " << bagNum << endl; 
		} else {
			cout << "The item was unsuccessfull in its removal" << endl;
		}
		break;
	
	case '4':				//Check if an item is in the bag
		cout << "Check if item is present: " << endl;
		item = getItem();
		bagNum = getBagNum();
		if (bag[bagNum].contains(item)) {
			cout << "The item " << item << " is present in bag " << bagNum << endl;
		} else {
			cout << "The item " << item << " was not found in bag " << bagNum << endl;
		}
		break;
	
	case '5':				//Join two bags together
		bag[0] = bag[1].bagUnion(bag[2]);
		
		displayBag(bag[0]);
		
		if (bag[1].getCurrentSize() + bag[2].getCurrentSize() > 6) {		//checks to see if the bags to be unionized are larger than the bag size
			cout << "There were too many items to add, not all items were added" << endl;
		} else {
			cout << "The items from both bags were added successfully" << endl;
		}
		bag[0].clear();
		break;
		
	case '6':				// Puts common items from two bags into a new bag
		bag[0] = bag[1].bagIntersection(bag[2]);
		
		displayBag(bag[0]);
		
		
		cout << "The items from both bags were added successfully" << endl;
		
		bag[0].clear();
		break;
	
    case '7':               // Display entire contents of bag
       displayBag(bag[getBagNum()]);
       break;

    case '8':               // Exit the program
    case 'Q':               // handles multiple quit inputs
    case 'q':
       cout<< "Would you like to save the bag to a file? (Y/N) ";
       getline(cin, saveBagFlg);
       if(saveBagFlg[0] == 'Y' || saveBagFlg[0] == 'y')
         saveBag(bag[getBagNum()]);         // save bag to file
       cout<< "Goodbye!"<< endl;  // Exit message
       menuChar = '8';
       break;
    default:                      // Invalid menu option entered
       cout << "\nError!  Invalid option.  Please try again.\n\n";
       printMenu();
    }
}//processOption()

/**
  * Restore the bag from a user specified file
  * @param[inout] bag restored from input file
  * @post The bag contains all items in the file if size < max bag list.
  * @remarks Prompt the user for the filename to retore the bag from.
  * If cannot open file, then reprompt user for filename.
  * Read items from file until end of file (eof) reached
  *  or until the bag is full.
  * Print the number of items read from the file.
  */
void restoreBag(Bag<string>& bag)
{
  bool success = true;
  ifstream fin;
  string filename;
  string item;

  //Data validation to get filename and open it
  do{
    cout<<"Enter the filename that contains the bag: ";
    getline(cin, filename);
    fin.clear();
    fin.open(filename.c_str());
    if(fin == 0){
      cout<<"ERROR  - could not open file " << filename<<endl;
    }
  } while (!fin);

  //read file until eof reached
  while(success && getline(fin,item)){
    success = bag.add(item);
  }
  if (!success) cout << "Not all items added to the bag!" << endl;
  cout<< bag.getCurrentSize() << " items read into the bag\n\n";
  fin.close();
}//restoreBag()

/**
  * Prompts the user for the filename to store the bag in.
  * @param[in] bag to be saved to a user specified file
  */
void saveBag(Bag<string>& bag)
{
	vector<string> bagVector = bag.toVector();
	
	if (bag.isEmpty()) {
		cout << "This bag is empty fool" << endl;
	
	} else {
		string filename;
		cout << "What would you like to name this file?" << endl;
		cin >> filename;
		ofstream saveFile (filename.c_str());
	
		//Add each item from the bag into the file by line
		for (int i = 0; i < bag.getCurrentSize(); i++) {
			saveFile << bagVector[i] << endl;
		}
		saveFile.close();
		cout << "Your bag has been saved" << endl;
	}
}//saveBag()

