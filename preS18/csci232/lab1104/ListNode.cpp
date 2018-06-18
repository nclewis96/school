/** @file Node.cpp */
#ifndef _LISTNODEIMP
#define _LISTNODEIMP

#include "ListNode.h"
#include <cstddef>

template < class ItemType >
ListNode < ItemType >::ListNode ():next (nullptr)
{
}   // end default constructor

template < class ItemType >
ListNode < ItemType >::ListNode (const ItemType & anItem): item (anItem), next (nullptr)
{
}   // end constructor

template < class ItemType >
ListNode < ItemType >::ListNode (const ItemType & anItem,
			 ListNode < ItemType > *nextNodePtr): item (anItem),
							  next (nextNodePtr)
{
}   // end constructor


#endif