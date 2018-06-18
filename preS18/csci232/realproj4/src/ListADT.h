/*
 * @file ListADT.h 
 * 
 * Phillip J. Curtiss, Assistant Professor
 * Computer Science Department, Montana Tech
 * F15 CSCI232 - Lab 11/04 - Inheritance and Operator Overloading
 */
#ifndef _LISTADT
#define _LISTADT

// ListInterface description
#include "ListInterface.h"

// As-is relationship to ListNode
#include "ListNode.h"

// Standard exception handling classes
#include <stdexcept>

// Required for overloading operator<< from ostream class
#include <ostream>

/** @class ListADT ListADT.h "ListADT.h"
 * ListADT defines a class representing a list of items
 * where the items are in a user defined position within
 * the list
 */
template<class ItemType>
class ListADT: public ListInterface<ItemType>
{
// Friend Declarations almost always come first
// before standard class access decorators (public, protected, private)
// This friend declarattion grants access to the ostream class for any 
// private or protected members from the ListADT class. This is needed as the
// operator<< must have access to internal data members in order to produce the 
// correct output - note that since ListADT and ostream are template classes we
// must chose a generic template that is not the same as that of ListADT
	template<class friendItemType>
	friend std::ostream& operator<<(std::ostream& outputStream, const ListADT<friendItemType>& outputList);

private:
	int itemCount; // Used to hold the number of items in the list
	ListNode<ItemType> *headPtr; // Used as the head pointer of the linked list of items
	
	/** Return a pointer to a node in the linked list from a given position provided
	 *  as a parameter
	 * @pre none
	 * @post none
	 * @param position and integer representing a position in the linked list
	 * @return a pointer to a node in the linked list corresponding to the position parameter */
	ListNode<ItemType>* getNodeAt(int position) const;
	
	/** Return an item from a given node in the linked list 
	 * @pre a pointer to a node in the list must be valid and in the linked list
	 * @post none
	 * @param node is a pointer to a node in the linked list
	 * @return an item of ItemType corresponding to the node pointer 
	 * @comment Accessor method for item in ListNode class */
	ItemType getItem(ListNode<ItemType> *node) const throw(std::invalid_argument);
	
	/** Return a node pointer to the next data member of a node provided as a 
	 *  parameter 
	 * @pre a pointer to a node in the list must be valid and in the linked list
	 * @post none
	 * @param a pointer to a node in the linked list
	 * @return the next data member of the node pointer parameter 
	 * @comment Accessor method for next in ListNode class */
	ListNode<ItemType>* getNext(ListNode<ItemType> *node) const throw(std::invalid_argument);
	
public:
	/** Default constructor: Creates an instance of a ListADT and initializes its
	 *  itemCount and headPtr data members to default values
	 * @pre none
	 * @post a new instance of a ListADT with default data member values */
	ListADT();
	
	/** Constrcutor: Creates an instance of a ListADT with initial values based on
	 *  a ListADT passed into the constructor as a parameter. The Constrctor makes
	 *  a deep copy of the parameter ListADT. Data members are set to correspond with 
	 *  the ListADT parameter
	 * @pre a ListADT object that is passed as a parameter to the constrctor
	 * @post a new instance of a ListADT with a deep copy of the ListADT parameter
	 * @param aList is a ListADT object instance */
	ListADT(const ListADT<ItemType>& aList);
	
	/** Default destructor: Destroys the ListADT object taking care to free memory 
	 *  allocated for the linked list structure.
	 * @pre none
	 * @post the freeing of allocated memory for the linkec list structure
	 * @commend this is a virtual method and should be overridden if this class is 
	 * inherited by another class */
	virtual ~ ListADT();
	
	/** Tests whether the ListADT is empty - i.e. has no nodes in its linked list
	 * @pre none
	 * @post none
	 * @return boolean value indicating whether the linked list has no nodes or 
	 * at least one node - we test itemCount */
	bool isEmpty() const;
	
	/** Returns the length of the ListADT - i.e. the number of nodes in the linked
	 *  list structure
	 * @pre none
	 * @post none
	 * @return an integer representing the number of nodes in the linked list structure */
	int getLength() const;
	
	/** Inserts a newEntry of ItemType into the list at a given position within the list
	 * @pre the position must be valid in the list - i.e. 0 < position <= getLength() + 1
	 * @post new item in the linked list structure at the specified position
	 * @param a position at which to insert the new item 
	 * @param newEntry the node to insert itno the linked list at the specified position
	 * @return boolean value as to the success of the entry of the newEnter into the linked
	 * list structure */
	bool insert(int newPosition, const ItemType& newEntry);
	
	/** Removes a node from the linked list structure at a given position
	 * @pre the position must be valid in the list - i.e. 0 < position <= getLength()
	 * @post the node at the specified position is removed from the list
	 * @param position is an integer representing a valid position in the linked list
	 * @return boolean value as to the success of the removal of the node at the
	 * specified position */
	bool remove(int position);
	
	/** Removes all nodes from the linked list and sets the itemCount and headPtr accordingly
	 * @pre none
	 * @post the linked list of nodes of items in the list is freed and the nodes deleted */
	void clear();
	
	/** Returns the item portion of a node found at the specified position 
	 * @pre the position must be valid in the list - i.e. 0 < position <= getLength()
	 * @post none
	 * @return the item portion of the node specified by the provided position */
	ItemType getEntry(int position) const throw(std::out_of_range);
	
	/** Replaces the node in the linked list structure corresponding to the specified position
	 * @pre the position must be valid in the list - i.e. 0 < position <= getLength()
	 * @post the node at the specified position is replaced with the newEntry parameter
	 * @param position is an int representing a valid location within the linked list
	 * @param newEntry is a node to place in the linked list at the specified position */
	void setEntry(int position, const ItemType& newEntry);

	/** Return the position within the linked list correspnding to the node parameter 
	 * @pre the entry must be a node compared to the nodes in the linked list 
	 * @post none
	 * @param entry is a node used to search through the linked list
	 * @return the position within the linked list structure at which the node is found */
	int getPosition(const ItemType& entry);	
	
	/** Returns a boolean value as to whether a given node is contained in the linked list
	 * @pre the entry must be a node to compare to the nodes in the linked list
	 * @post none
	 * @param entry is a node used to search through the linked list
	 * @return a boolean value as to the success of finding the entry in the linked list */
	bool contains(const ItemType& entry);
	
	/** Returns a boolean value as to the sameness comparison of two ListADT object instances
	 * @pre two ListADT object instances must exist (lhs == rhs)
	 * @post none
	 * @param the right hand side (rhs) of the == operator - used to compare to the instance object
	 * @return boolean value representing the sameness of the two instance objects compared */
	bool operator==(const ListADT<ItemType>& rhs) const;
	
	/** Returns a concatenated instance of the ListADT object from two other instance objects
	 * @pre two ListADT object instances must exist (lhs + rhs)
	 * @post a new ListADT representing the concatenated ListADT objects as operands
	 * @return the new ListADT formed from the concatenation of the two ListADT objects as operands */
	ListADT<ItemType> operator+(const ListADT<ItemType>& rhs);
};

#include "ListADT.cpp"
#endif
