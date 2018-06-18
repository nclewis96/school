/*
 * @file ListNode.cpp 
 * 
 * Phillip J. Curtiss, Assistant Professor
 * Computer Science Department, Montana Tech
 * F15 CSCI232 - Lab 11/04 - Inheritance and Operator Overloading
 */
#ifndef _LISTNODEIMP
#define _LISTNODEIMP

// ListNode class description
#include "ListNode.h"

template<class ItemType>
ListNode<ItemType>::ListNode(): next(nullptr) {}
// end default constructor - sets next to nullptr

template<class ItemType>
ListNode<ItemType>::ListNode(const ItemType& anItem): item(anItem), next(nullptr) {}
// end constructor - initializes item from parameter and sets next to nullptr

template<class ItemType>
ListNode<ItemType>::ListNode(const ItemType& anItem, ListNode<ItemType>* nextNodePtr): item(anItem), next(nextNodePtr) {}
// end constructor - initializes item from parameter and next from parameter

#endif
