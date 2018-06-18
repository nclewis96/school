
#ifndef _LINKEDBAGIMP
#define _LINKEDBAGIMP

#include "BagInterface.h"
#include "LinkedBag.h"

#include <iostream>
#include <string>
#include <cstddef>
#include <vector>

using namespace std;

template<class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0)
{
} //end default constructor

template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry)
{
   ListNode<ItemType>* newNodePtr = new ListNode<ItemType>();
   newNodePtr->item = (newEntry);
   newNodePtr->next = (headPtr);
   headPtr = newNodePtr;
   itemCount++;

   return true;
} // end of add

template<class ItemType>
std::vector<ItemType> LinkedBag<ItemType>::toVector() const
{
   std::vector<ItemType> bagContents;
   ListNode<ItemType>* curPtr = headPtr;
   int counter = 0;

   while( (curPtr != nullptr) && (counter < itemCount) )
   {
      bagContents.push_back(curPtr-> item);
      curPtr = curPtr -> next;
      counter++;
   } //end while

   return bagContents;
} // end of toVector

template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const
{
   return (itemCount == 0);
} // end of isEmpty

template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const
{
   return itemCount;
} // end of getCurrentSize

template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
   int frequency = 0;
   int counter = 0;
   ListNode<ItemType>* curPtr = headPtr;

   while( (curPtr != nullptr) && (counter < itemCount) )
   {
      if (anEntry == curPtr-> item)
      {
         frequency++;
      }
      counter++;
      curPtr = curPtr-> next;
   } //end while 

   return frequency;
} // end of getFrequencyOf

template<class ItemType>
ListNode<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& target) const
{
   bool found = false; 
   ListNode<ItemType>* curPtr = headPtr;

   while( !found && (curPtr != nullptr))
   {
      if (target == curPtr-> item)
         found = true;
      else
         curPtr = curPtr->next;
   } // end while

   return curPtr;
} // end of getPointerTo

template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
   return (getPointerTo(anEntry) != nullptr);
}  // end of contains

template<class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry)
{
   ListNode<ItemType>* entryNodePtr = getPointerTo(anEntry);
   bool canRemoveItem = (!isEmpty() && (entryNodePtr != nullptr));

   if (canRemoveItem)
   {
      //Copy data from first node to located node
      entryNodePtr->item = (headPtr->item);

      //Delete first node
      ListNode<ItemType>* nodeToDeletePtr = headPtr;
      headPtr = headPtr->next;

      // Free the node memory
      nodeToDeletePtr-> next = (nullptr);
      delete nodeToDeletePtr;
      nodeToDeletePtr = nullptr;

      itemCount--;
   } //end if

   return canRemoveItem;
} // end of remove

template<class ItemType>
void LinkedBag<ItemType>::clear()
{
   while(headPtr != nullptr)
   {
      ListNode<ItemType>* nodeToDeletePtr = headPtr; 
      headPtr = headPtr-> next;

      // Free the node memory
      nodeToDeletePtr-> next = nullptr;
      delete nodeToDeletePtr;
   } //end of while

   itemCount = 0;
} // end of clear

template<class ItemType>
LinkedBag<ItemType>::~LinkedBag()
{
   clear();
} // end of destructor

template<class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag)
{
   itemCount = aBag.itemCount;
   ListNode<ItemType>* origChainPtr = aBag.headPtr;

   if (origChainPtr == nullptr)
      headPtr = nullptr; // original bag is empty so no copy
   else
   {
      // Copy first node
      headPtr = new ListNode<ItemType>();
      headPtr->item = (origChainPtr-> item);

      // Copy remaining nodes
      ListNode<ItemType>* newChainPtr = headPtr; // last-node pointer
      while(origChainPtr != nullptr)
      {
         origChainPtr = origChainPtr->next; // Advance pointer
         
         // Get next item from original chain
         ItemType nextItem = origChainPtr->item;

         // Create a new node containing the next item
         ListNode<ItemType>* newNodePtr = new ListNode<ItemType>(nextItem);

         // Link new node to end of new chain
         newChainPtr->next = (newNodePtr);

         // Advance Pointer to new last node
         newChainPtr= newChainPtr -> next;
      } // end while

      // Flag the end of the new chain
      newChainPtr->next = nullptr;
   } //end if
} // end of copy constructor

//overloads the '==' operator to allow 2 bags to be compared.
template<class ItemType>
bool LinkedBag<ItemType>::operator==(const LinkedBag<ItemType>& rhs) const {
	bool isEqual = true;
	ListNode<ItemType>* rhsPtr = rhs.headPtr;
	
	if(getCurrentSize() != rhs.getCurrentSize() ){
		isEqual = false;
	}else{
		
		
		while(isEqual && rhsPtr != nullptr){
		   int rhsFreq = rhs.getFrequencyOf(rhsPtr -> item );
		   int lhsFreq =     getFrequencyOf(rhsPtr -> item );
		   
		   if(rhsFreq == lhsFreq ){
		      isEqual = true;
		   }else {
		   	  isEqual = false;
		   }
		   
		   rhsPtr = rhsPtr -> next;
		
		
		}
	} 
	
	return isEqual;

}//end of operator==

//overloads the '+' operator to allow 2 bags to be added together.
template<class ItemType>
LinkedBag<ItemType> LinkedBag<ItemType>::operator+(const LinkedBag<ItemType>& rhs) const{
	LinkedBag<ItemType> Bag = LinkedBag<ItemType>();
	
	
	ListNode<ItemType>* lhsPtr = headPtr;
	while(lhsPtr != nullptr){
	   Bag.add( lhsPtr ->item );
	   lhsPtr = lhsPtr -> next;
	}
	
	//adds all entries from the bag on the right hand side
    ListNode <ItemType>* rhsPtr = rhs.headPtr;
    while(rhsPtr != nullptr){
	   Bag.add( rhsPtr ->item );
	   rhsPtr = rhsPtr -> next;
	}
	
	
	
	return Bag;
}//end of operator+

//overloads the << operator to allow an easy print out method
template<class friendItemType>
ostream& operator<<(ostream& outStream, const LinkedBag<friendItemType>& outputList){     
    int position = 1;
 	ListNode<friendItemType>* curPtr = outputList.headPtr; 
 	while (curPtr != nullptr)
    {
       outStream << position << "\t" << outputList.getItem(curPtr) << endl; 
       curPtr = outputList.getNext(curPtr);
       position++;
    } // end while 
    return outStream;

}//end of operator <<

template<class ItemType>
ItemType LinkedBag<ItemType>::getItem(ListNode<ItemType>* n) const {
   return n -> item;
}

template<class ItemType>
ListNode<ItemType>* LinkedBag<ItemType>::getNext(ListNode<ItemType>* n) const {
   return n -> next;
}

#endif

