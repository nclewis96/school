/*
 * @file ListNode.h 
 * 
 * Phillip J. Curtiss, Assistant Professor
 * Computer Science Department, Montana Tech
 * F15 CSCI232 - Lab 11/04 - Inheritance and Operator Overloading
 */
#ifndef _LISTNODE
#define _LISTNODE

/** @class ListNode ListNode.h "ListNode.h"
 * ListNode is a private class used to support other classes
 * such as ListADT. This establishes an as-a relationship 
 * between the ListNode class and the ListADT class.
 */
template < class ItemType>
class ListNode
{
	// This entire class is private, therefore we must
	// explicity grant access to private members using 
	// the friend construct. Since ListADT is a template
	// class, we provide a generic template here, different
	// from the template ListNode is using.
	template <class U>
	friend class ListADT;
	
	// Private constructors means that only classes specifically
	// granted access by the ListNode class can use instances of
	// ListNode
    private :
	    ItemType item;				// A data item
	    ListNode<ItemType>* next;	// Pointer to next node

		/** Default constructor: Creates an instance of a ListNode
		 *  and inializes data members
		 * @pre None.
		 * @post A ListNode instance */
	    ListNode();
		
		/** Constructor: Creates a ListNode with its item initialized
		 *  to the parameter provided
		 * @pre anItem is an ItemType previously created
		 * @post A ListNode instance with its item data member initialized
		 * @param anItem which represents an ItemType data type to initialize item */
	    ListNode( const ItemType& anItem);
		
		/** Constructor: Creates a ListNode with its item and next initialized
		 * @pre anItem is an ItemType previously created
		 * @pre nextNodePtr is a pointer to ListNode<ItemType> previously created
		 * @post A ListNode instance with its item and next data members initialized
		 * @param anItem which represents an ItemType data type to initialize item
		 * @param nextNodePtr which represents a pointer of ListNode<ItemType> to initialize next */
	    ListNode( const ItemType& anItem, ListNode<ItemType>* nextNodePtr);

}; // end ListNode
#include "ListNode.cpp"
#endif

