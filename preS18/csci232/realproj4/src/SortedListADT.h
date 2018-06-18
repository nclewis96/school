/*Nathaniel Lewis
 * nlewis
 * nlewis
 * @file SortedListADT.h 
 * 
 */
#ifndef _SORTEDLISTADT
#define _SORTEDLISTADT

// SortedListInterface description
#include "SortedListInterface.h"
#include "ListADT.h"

// Standard exception handling classes
#include <stdexcept>
#include <iostream>
#include <fstream>

/** @class SortedListADT SortedListADT.h "SortedListADT.h"
 * SortedListADT defines a class representing a sorted list of items
 * where the items are in an order represented by a sort index
 */
template<class ItemType>
class SortedListADT: public SortedListInterface<ItemType>,
                     private ListADT<ItemType>
{

 // Friend Declarations almost always come first
// before standard class access decorators (public, protected, private)
// This friend declarattion grants access to the ostream class for any 
// private or protected members from the ListADT class. This is needed as the
// operator<< must have access to internal data members in order to produce the 
// correct output - note that since ListADT and ostream are template classes we
// must chose a generic template that is not the same as that of ListADT
	template<class friendItemType>
	friend ostream& operator<<(ostream& outputStream, const SortedListADT<friendItemType>& outputList);
	
private:
	
		// Place your private data members and methods here
		
public:
	/** Default constructor: Creates an instance of a ListADT and initializes its
	 *  itemCount and headPtr data members to default values
	 * @pre none
	 * @post a new instance of a SortedListADT with default data member values */
	SortedListADT();
	
	/** Constrcutor: Creates an instance of a SortedListADT with initial values based on
	 *  a ListADT passed into the constructor as a parameter. The Constrctor makes
	 *  a deep copy of the parameter SortedListADT. Data members are set to correspond with 
	 *  the ListADT parameter
	 * @pre a ListADT object that is passed as a parameter to the constrctor
	 * @post a new instance of a SortedListADT with a deep copy of the SortedListADT parameter
	 * @param aList is a ListADT object instance */
	SortedListADT(const SortedListADT<ItemType>& aList);
	
	/** Default destructor: Destroys the ListADT object taking care to free memory 
	 *  allocated for the linked list structure.
	 * @pre none
	 * @post the freeing of allocated memory for the linkec list structure
	 * @commend this is a virtual method and should be overridden if this class is 
	 * inherited by another class */
	virtual ~SortedListADT();
	
	/** Checks if the list is empty
	*@pre none
	*@post none
	*@param none
	*return bool showing if the link is empty or not*/
	bool isEmpty() const;
	
	/** Return the number of data items in the list
	*@pre none
	*@post
	*@param none
	*return integer that's the */
	int getLength() const;
	
	/** Inserts a data member into an ordered place
	*@pre 
	*@post places entry in the List in order 
	*@param an entry to be placed into the list
	*return none */
	void insertSorted(const ItemType& newEntry);
	
	/**  Removes an object from the array
	*@pre  The object to be removed is contained inside the list
	*@post 
	*@param entry to be removed from the List
	*return boolean representing if the entry was removed from the list*/
	bool removeSorted(const ItemType& entry);
	
	/** Removes the Node at the given position
	*@pre The position is inside the length of the array
	*@post List is shortened by one and shifted
	*@param position of the entry to be removed from the list
	*return boolean representing if the entry was removed from the list */
	bool remove(int position);
	
	/** Deletes all the Nodes from the List
	*@pre none
	*@post none
	*@param none
	*return none*/
	void clear();
	
	/** Returns an Entry at the given position
	*@pre 
	*@post none
	*@param A position in the List
	*return an Item at the given position  */
	ItemType getEntry (int position) const throw(std::out_of_range);
	
	/** Get's either the position of an entry in the list or where it should be
	*@pre 
	*@post
	*@param
	*return */
	int getPosition(const ItemType& entry);
	
	/** Checks if the given entry is contained in the list
	*@pre none
	*@post none
	*@param an entry to check
	*return bool showing if the entry is or is not contained inside the list*/
	bool contains(const ItemType& entry);
	
	/** Loads the list from a file
	*@pre the file to exist
	*@post a sorted list that 
	*@param an existing file
	*return */
	bool loadList( string filename);
	
	/** prints the list out to the console
	*@pre 
	*@post
	*@param
	*return none */
	void displayList() const;
	
		
	/** Returns a boolean value as to the sameness comparison of two ListADT object instances
	 * @pre two ListADT object instances must exist (lhs == rhs)
	 * @post none
	 * @param the right hand side (rhs) of the == operator - used to compare to the instance object
	 * @return boolean value representing the sameness of the two instance objects compared */
	bool operator==(const SortedListADT<ItemType>& rhs) const;
	
	/** Returns a concatenated instance of the ListADT object from two other instance objects
	 * @pre two ListADT object instances must exist (lhs + rhs)
	 * @post a new ListADT representing the concatenated ListADT objects as operands
	 * @return the new ListADT formed from the concatenation of the two ListADT objects as operands */
	SortedListADT<ItemType> operator+(const SortedListADT<ItemType>& rhs) const;	
	
};

#include "SortedListADT.cpp"
#endif
