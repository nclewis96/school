/** @file ListNode.h */
#ifndef _LISTNODE
#define _LISTNODE
template < class ItemType>
class ListNode
{
    
    private :
	    ItemType item; // A data item
	    ListNode<ItemType>* next; // Pointer to next node
	    
	    ListNode();
	    ListNode( const ItemType& anItem);
	    ListNode( const ItemType& anItem, ListNode<ItemType>* nextNodePtr);
	    
	    template<class M>
	    friend class LinkedBag;
    
	   
}; // end Node
#include "ListNode.cpp"
#endif

