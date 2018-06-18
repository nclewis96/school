//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file Bag.cpp (same as ArrayBag) */
#ifndef _BAGIMP
#define	_BAGIMP
#include "Bag.h"
#include <cstddef>
#include "io_functions.h"

using namespace std;

template<class ItemType>
Bag<ItemType>::Bag() : itemCount(0), maxItems(DEFAULT_BAG_SIZE)
{
}  // end default constructor

template<class ItemType>
int Bag<ItemType>::getCurrentSize() const
{
	return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool Bag<ItemType>::isEmpty() const
{
	return itemCount == 0;
}  // end isEmpty

template<class ItemType>
bool Bag<ItemType>::add(const ItemType& newEntry)
{
	bool hasRoomToAdd = (itemCount < maxItems);
	if (hasRoomToAdd)
	{
		items[itemCount] = newEntry;
		itemCount++;
	}  // end if
    
	return hasRoomToAdd;
}  // end add

template<class ItemType>
bool Bag<ItemType>::remove(const ItemType& anEntry)
{
   int locatedIndex = getIndexOf(anEntry);
	bool canRemoveItem = !isEmpty() && (locatedIndex > -1);
	if (canRemoveItem)
	{
		itemCount--;
		items[locatedIndex] = items[itemCount];
	}  // end if
    
	return canRemoveItem;
}  // end remove

template<class ItemType>
void Bag<ItemType>::clear()
{
	itemCount = 0;
}  // end clear

template<class ItemType>
int Bag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
   int frequency = 0;
   int searchIndex = 0;
   while (searchIndex < itemCount)
   {
      if (items[searchIndex] == anEntry)
      {
         frequency++;
      }  // end if
      
      searchIndex++;
   }  // end while
   
   return frequency;
}  // end getFrequencyOf

template<class ItemType>
bool Bag<ItemType>::contains(const ItemType& anEntry) const
{
	return getIndexOf(anEntry) > -1;
}  // end contains

/* ALTERNATE 1
template<class ItemType>
bool Bag<ItemType>::contains(const ItemType& anEntry) const
{
	return getFrequencyOf(anEntry) > 0;
}  // end contains
*/
/* ALTERNATE 2 
template<class ItemType>
bool Bag<ItemType>::contains(const ItemType& anEntry) const
{
   bool found = false;
   for (int i = 0; !found && (i < itemCount); i++)
   {
      if (anEntry == items[i])
      {
         found = true;
      } // end if
   } // end for
   
   return found;
}  // end contains
*/

template<class ItemType>
vector<ItemType> Bag<ItemType>::toVector() const
{
	vector<ItemType> bagContents;
	for (int i = 0; i < itemCount; i++)
		bagContents.push_back(items[i]);
   return bagContents;
}  // end toVector

// private
template<class ItemType>
int Bag<ItemType>::getIndexOf(const ItemType& target) const
{
	bool found = false;
   int result = -1;
   int searchIndex = 0;
   // if the bag is empty, itemCount is zero, so loop is skipped
   while (!found && (searchIndex < itemCount))
   {
      if (items[searchIndex] == target)
      {
         found = true;
         result = searchIndex;
      } 
      else
      {
         searchIndex++;
      }  // end if
   }  // end while
   
   return result;
}  // end getIndexOf

template<class ItemType>
	Bag<ItemType> Bag<ItemType>::bagUnion(const Bag<ItemType> bag) const
{
	Bag<ItemType> bag3;
	
	
	if (!bag.isEmpty()) {								/*Add items from the given bag to the new one 
														as long as it's not empty*/
		for (int i = 0; i < bag.getCurrentSize(); i++) { 
			bag3.add(bag.items[i]);
		}
	} else {
		cout << "The given bag is empty" << endl;
	}//end if
	
	
	if (bag3.getCurrentSize() < maxItems) {				/*Add items from the current bag into the 
														new one as long as there is room*/
		for (int i = 0; i < getCurrentSize(); i++) {
			bag3.add(items[i]);
		}
	} 
	else
	{
		cout << "The new bag is full" << endl;
	}//end if
	
	return bag3;
}

template<class ItemType>
	Bag<ItemType> Bag<ItemType>::bagIntersection(const Bag<ItemType> bag) const
{
	Bag<ItemType> bag3;
	
	bool visited[bag.getCurrentSize()];					//Used to check if an item has already been compared	
	for (int i = 0; i < bag.getCurrentSize(); i++) {
		visited[i] = false;
	}
	
	for (int i = 0; i < getCurrentSize(); i++) {		/*Adds the common items from both bags until the bag 
														is either full or there are no more items to add*/
													
		if (contains(bag.items[i]) && !visited[i]) {	/*check if the item is also in the current bag 
														and has not been checked yet*/
			bag3.add(bag.items[i]);
			visited[i] = true;
		} //end if
	}
	
	return bag3;
}

#endif