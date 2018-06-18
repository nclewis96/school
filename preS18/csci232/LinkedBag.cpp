
#ifndef _LINKEDBAGIMP
#define _LINKEDBAGIMP

#include "BagInterface.h"
#include "LinkedBag.h"

#include <iostream>
#include <string>
#include <cstddef>

template<class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0)
{
} //end default constructor

template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry)
{
   Node<ItemType>* newNodePtr = new Node<ItemType>();
   newNodePtr->setItem(newEntry);
   newNodePtr->setNext(headPtr);
   headPtr = newNodePtr;
   itemCount++;

   return true;
} // end of add

template<class ItemType>
std::vector<ItemType> LinkedBag<ItemType>::toVector() const
{
   std::vector<ItemType> bagContents;
   Node<ItemType>* curPtr = headPtr;
   int counter = 0;

   while( (curPtr != nullptr) && (counter < itemCount) )
   {
      bagContents.push_back(curPtr->getItem());
      curPtr = curPtr->getNext();
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
   Node<ItemType>* curPtr = headPtr;

   while( (curPtr != nullptr) && (counter < itemCount) )
   {
      if (anEntry == curPtr->getItem())
      {
         frequency++;
      }
      counter++;
      curPtr = curPtr->getNext();
   } //end while 

   return frequency;
} // end of getFrequencyOf

template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& target) const
{
   bool found = false; 
   Node<ItemType>* curPtr = headPtr;

   while( !found && (curPtr != nullptr))
   {
      if (target == curPtr->getItem())
         found = true;
      else
         curPtr = curPtr->getNext();
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
   Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
   bool canRemoveItem = (!isEmpty() && (entryNodePtr != nullptr));

   if (canRemoveItem)
   {
      //Copy data from first node to located node
      entryNodePtr->setItem(headPtr->getItem());

      //Delete first node
      Node<ItemType>* nodeToDeletePtr = headPtr;
      headPtr = headPtr->getNext();

      // Free the node memory
      nodeToDeletePtr->setNext(nullptr);
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
      Node<ItemType>* nodeToDeletePtr = headPtr; 
      headPtr = headPtr->getNext();

      // Free the node memory
      nodeToDeletePtr->setNext(nullptr);
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
   itemCount = aBag->itemCount;
   Node<ItemType>* origChainPtr = aBag->headPtr;

   if (origChainPtr == nullptr)
      headPtr = nullptr; // original bag is empty so no copy
   else
   {
      // Copy first node
      headPtr = new Node<ItemType>();
      headPtr->setItem(origChainPtr->getItem());

      // Copy remaining nodes
      Node<ItemType>* newChainPtr = headPtr; // last-node pointer
      while(origChainPtr != nullptr)
      {
         origChainPtr = origChainPtr->getNext(); // Advance pointer
         
         // Get next item from original chain
         ItemType nextItem = origChainPtr->getItem();

         // Create a new node containing the next item
         Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

         // Link new node to end of new chain
         newChainPtr->setNext(newNodePtr);

         // Advance Pointer to new last node
         newChainPtr= newChainPtr->getNext();
      } // end while

      // Flag the end of the new chain
      newChainPtr->setNext(nullptr);
   } //end if
} // end of copy constructor


template<class ItemType>
bool LikedBag<ItemType>::operator==(const LinkedBag<ItemType> rhs){
	bool isEqual;
	if(getCurrentSize() == rhs.getCurrentSize() ){
		Node<ItemType>* rhsPtr = rhs.headPtr;
		
		while(isEqual && rhs != nullptr){
		   int rhsFreq = rhs.getFrequencyOf(rhsPtr -> getItem() );
		   int lhsFreq = getFrequencyOf(rhsPtr -> getItem() );
			
		   if(rhsFreq == lhsFreq ){
		      isEqual = true;
		   }else {
		   	  isEqual = false;
		   }
		   rhsPtr = rhsPtr -> getNext();
		
		
		}
	} else {
	   isEqual = false;
	}
	
	return isEqual;

}

template<class ItemType>
LinkedBag<ItemType>::operator+(const LinkedBag<ItemType> rhs){
    rhsPtr = rhs.headPtr;
    while(rhsPtr != nullptr){
	   add( rhsPtr ->getItem() );
	   rhsPtr = rhsPtr -> getNext();
	}
}

template<class friendItemType>
std::ostream& operator<<(ostream& outStream, const LinkedBag<friendItemType>& outputList){     
    int position = 1;
 	Node<friendItemType>* curPtr = outputList.headPtr; 
 	while (curPtr != nullptr)
    {
       outStream << position << "\t" << curPtr->getItem() << endl; curPtr = curPtr->getNext();
       position++;
    } // end while 
    return outStream;

}
#endif

