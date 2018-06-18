/*
 * @file ListADT.cpp 
 * 
 * Phillip J. Curtiss, Assistant Professor
 * Computer Science Department, Montana Tech
 * F15 CSCI232 - Lab 11/04 - Inheritance and Operator Overloading
 */
#ifndef _LISTADTIMP
#define _LISTADTIMP

// ListADT class description 
#include "ListADT.h"

// ListNode class description
// Implemented as-a class relationship
#include "ListNode.h"

// Standard exception handling classes
#include <stdexcept>

// Used to override the operator<<
#include <ostream>

template<class ItemType>
ListADT<ItemType>::ListADT(): itemCount(0), headPtr(nullptr) {}
// end default constructor - sets itemCount and headPtr to default values

template<class ItemType>
ListADT<ItemType>::ListADT(const ListADT<ItemType>& aList)
{
	// Initialize our data members
	itemCount = 0;
	headPtr = nullptr;
	
	// Iterate through the nodes in the parameter linked list and create new
	// nodes initialized to the item of the parameter linked list node and 
	// add to our linked list
	for (ListNode<ItemType> *aListPtr = aList.headPtr; aListPtr != nullptr; aListPtr = aListPtr->next)
		(void) ListADT<ItemType>::insert(itemCount + 1, aListPtr->item);
	
} // end copy constructor - deep copy of ListADT param

template<class ItemType>
ListADT<ItemType>::~ListADT()
{
	// Call clear to clear the linked list structure of this 
	// object instance
	ListADT<ItemType>::clear();
	
} // end default destructor

template<class ItemType>
ListNode<ItemType>* ListADT<ItemType>::getNodeAt(int position) const
{
	// Initialize our current point to the nullptr to return 
	// if position is out of bounds
	ListNode<ItemType> *curPtr = nullptr;
	
	// If position is in bounds of linked list 
	if (position >= 1 && position <= itemCount)
	{
		// Set current pointer to head of linked list and iterate
		// through the list until the requested position is reached
		curPtr = headPtr;
		for (int posIdx = 1; posIdx < position; posIdx++)
			curPtr = curPtr->next;		
	}
	
	// return the pointer at the requested position or 
	// nullptr if position is out of bounds
	return(curPtr);
} // end of getNodeAt method

template<class ItemType>
bool ListADT<ItemType>::isEmpty() const 
{ 
	// return boolean value reflecting if there
	// are any items in the linked list.
	return(itemCount == 0); 
	
} // end of isEmpty Method

template<class ItemType>
int ListADT<ItemType>::getLength() const 
{
	// return the number of items in the linked
	// list structure 
	return(itemCount);
	
}// end of getLength method 

template<class ItemType>
bool ListADT<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
	// Check to see if specified position is within the bound of the 
	// linked list + 1 to allow for new addition on the end
	if (newPosition >=1 && (newPosition <= itemCount + 1))
	{
		// Create a new ListNode initialized with the newEntry
		ListNode<ItemType> *newNodePtr = new ListNode<ItemType>(newEntry);
		
		// If the newEntry is to be placed at the head of the list...
		if (newPosition == 1)
		{
			newNodePtr->next = headPtr; // set next for new node to headPtr
			headPtr = newNodePtr; // set headPtr to the new node
		}
		else
		{
			// Get the previous node from the specified position
			ListNode<ItemType> *prevPtr = getNodeAt(newPosition - 1);
			
			newNodePtr->next = prevPtr->next; // set next for new node to next of prev node
			prevPtr->next = newNodePtr; // set next of prev node to the new node
		}
		
		// Increase the number of items in the linked list and return our 
		// success at the insert
		itemCount++;
		return(true);
	}
	
	// Return our failure to insert the newEntry
	return(false);
} // end of insert method

template<class ItemType>
ItemType ListADT<ItemType>::getEntry(int position) const throw(std::out_of_range) 
{
	// If the specified position is in range for the linked list,
	// then return the item associated with the node at the specified position
	if (position >= 1 && position <= itemCount)
		return(getNodeAt(position)->item);

	// If position is out of range, then throw exception
	throw std::out_of_range("Position out of bounds");
} // end of getEntry method

template<class ItemType>
void ListADT<ItemType>::setEntry(int position, const ItemType& newEntry) 
{
	// Find the node a the position specified
	ListNode<ItemType> *curPtr = getNodeAt(position);
	
	// If the node was found, set its item property to that specified
	if (curPtr != nullptr)
		curPtr->item = newEntry;
} // end of setEntry method

template<class ItemType>
int ListADT<ItemType>::getPosition(const ItemType& entry) 
{ 
	int position = 0;
	ListNode<ItemType> *curPtr = headPtr;
	
	// Iterate through the linked list comparing nodes until there is a match
	for (position = 0; curPtr != nullptr; curPtr = curPtr -> next, position++);
	
	// If match, then return position, otherwise -1
	if (curPtr != nullptr)
		return(position);
	else
		return(-1);
} // end of getPosition method

template<class ItemType>
bool ListADT<ItemType>::contains(const ItemType& entry) 
{ 
	ListNode<ItemType> *curPtr = nullptr;
	bool retVal = false;
	
	// Iterate through the linked list looking for entry and comparing to item
	// of every node in the linked list; if found, set retVal to true and stop iteration
	if (itemCount >= 1)
		for (curPtr = headPtr; curPtr != nullptr && retVal == false; curPtr = curPtr -> next)
			if (curPtr -> item == entry)
				retVal = true;
	
	// return result of search
	return(retVal);
} // end of contains method

template<class ItemType>
bool ListADT<ItemType>::remove(int position) 
{ 
	// If the position is within the bounds of the 
	// linked list 
	if (position >= 1 && position <= itemCount)
	{
		ListNode<ItemType> *curPtr = nullptr;
		
		// If to remove the headPtr, then ...
		if (position == 1)
		{
			curPtr = headPtr; // temp set curPtr to headPtr (node to be removed)
			headPtr = headPtr->next; // set headPtr now to next node in linked list
		}
		else
		{
			// Get previous node in the linked list
			ListNode<ItemType> *prevPtr = getNodeAt(position - 1);
			
			curPtr = prevPtr->next;	// temp set curPtr to node to be removed
			prevPtr->next = curPtr->next; // set prev node's next to curPtr node's next
		}
		
		// Remove node pointed to be curPtr and reduce itemCount
		curPtr->next = nullptr;
		delete curPtr;
		curPtr = nullptr;
		itemCount--;
		
		// return our success
		return(true);
	}
	
	// return our failure
	return(false); 
} // end of remote method

template<class ItemType>
void ListADT<ItemType>::clear() 
{
	ListNode<ItemType> *curPtr = nullptr;
	
	// Set itemCount to reflect empty linked list
	itemCount = 0;
	
	// Iterate through nodes in linked list and remove the node
	// at the first position
	for (curPtr = headPtr; curPtr != nullptr; curPtr = curPtr -> next)
		remove(1);
} // end of clear method

template<class ItemType>
ItemType ListADT<ItemType>::getItem(ListNode<ItemType> *node) const throw(std::invalid_argument)
{
	// Return the item of the node pointer if not nullptr
	if (node != nullptr)
		return(node->item);
	
	// If nullptr as argument throw exception
	throw std::invalid_argument("Can't getItem of nullptr");
} // end of getItem method

template<class ItemType>
ListNode<ItemType>* ListADT<ItemType>::getNext(ListNode<ItemType> *node) const throw(std::invalid_argument)
{
	// Return the next of the node pointer if not nullptr
	if (node != nullptr)
		return(node->next);
	
	// If nullptr as argument throw exception
	throw std::invalid_argument("Can't getNext of nullptr");
} // end of getNext method

template<class ItemType>
bool ListADT<ItemType>::operator==(const ListADT<ItemType>& rhs) const
{
	bool isEqual = true;
	
	// If the linked lists are of different lengths, then we set our 
	// return value to false
	if (itemCount != rhs.getLength())
		isEqual = false;
	else
	{
		ListNode<ItemType>* lhsPtr = headPtr;
		ListNode<ItemType>* rhsPtr = rhs.headPtr;
		
		// Linked lists are the same length, so we now iterate through each
		// node from both lists and compare the item property for equality
		while ( (lhsPtr != nullptr) && (rhsPtr != nullptr) && isEqual)
		{
			ItemType lhsItem = lhsPtr->item;
			ItemType rhsItem = rhsPtr->item;
			isEqual = (lhsItem == rhsItem);
			
			lhsPtr = lhsPtr->next;
			rhsPtr = rhsPtr->next;
		}
	}
	
	// Return whether the linked list has identical nodes in the same order
	return (isEqual);
} // end of operator==

template<class ItemType>
ListADT<ItemType> ListADT<ItemType>::operator+(const ListADT<ItemType>& rhs)
{
	// Create a new ListADT object initialized from the linked list nodes
	// found in lhs operand - this pointer refers to the current instance object, 
	// which for C++ operators is always the lhs operand
	ListADT<ItemType> concatList = ListADT<ItemType>(*this);
	
	// iterate through the nodes in the rhs operant and add these to the new
	// ListADT at the end of the list (getLength() + 1)
	for (ListNode<ItemType> *curPtr = rhs.headPtr; curPtr != nullptr; curPtr = curPtr->next)
		concatList.insert(concatList.getLength() + 1, curPtr->item);

	// return the new ListADT that is concatenation of the lhs and rhs
	return(concatList);
} // end of operator++

template<class friendItemType>
ostream& operator<<(ostream& outStream, const ListADT<friendItemType>& outputList)
{
	// set curPtr to the headnode of the ListADT operand
	// create a variable curItem to hold the item property of a node
	ListNode<friendItemType> *curPtr = outputList.headPtr;
	friendItemType curItem;
	
	// Iterate through all the nodes in the linked list
	while (curPtr != nullptr)
	{
		curItem = outputList.getItem(curPtr); // Set the curItem to the item property of the current node
		curPtr = outputList.getNext(curPtr); // Set the curPtr to the next property of the current node
		outStream << curItem; // send to the outStream the item property
		if (curPtr != nullptr) // if the next node is not null, then send a space to outStream
			outStream << " ";
	}
	
	// return our outStream with the written contents from the 
	// ListADT linked list
	return (outStream);
} // end of ostream operator<< 

#endif
