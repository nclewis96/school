/* Nathaniel Lewis
 * nlewis
 * nlewis
 *
 * @file SortedListADT.cpp 
 * 
 */
#ifndef _SORTEDLISTADTIMP
#define _SORTEDLISTADTIMP

// ListADT class description 
#include "SortedListADT.h"

// ListADT class description
// Implemented is-a class relationship
#include "ListADT.h"

// Standard exception handling classes
#include <stdexcept>
#include <string>
#include <cmath>
// Used to override << operator
#include <iostream>

template<class ItemType>
SortedListADT<ItemType>::SortedListADT(){
}// end default constructor 


template<class ItemType>
SortedListADT<ItemType>::SortedListADT(const SortedListADT<ItemType>& aList)
{
   if(aList.isEmpty())
       return;
   for(int i = 1; i <= aList.getLength(); i++){
   insertSorted(aList.getEntry(i));
   }
} // end copy constructor - deep copy of SortedListADT param

template<class ItemType>
SortedListADT<ItemType>::~SortedListADT()
{
    clear();
	
} // end default destructor

template<class ItemType>
bool SortedListADT<ItemType>::isEmpty() const { 
   return ListADT<ItemType>::isEmpty(); 
}

template<class ItemType>
int SortedListADT<ItemType>::getLength() const{ 
   return ListADT<ItemType>::getLength();
}

template<class ItemType>
void SortedListADT<ItemType>::insertSorted(const ItemType& newEntry){
	ListADT<ItemType>::insert(getPosition(newEntry), newEntry);
}

template<class ItemType>
bool SortedListADT<ItemType>::removeSorted(const ItemType& entry){
   return remove(getPosition(entry));
}

template<class ItemType>
bool SortedListADT<ItemType>::remove(int position) { 
   return ListADT<ItemType>::remove(position);
}

template<class ItemType>
void SortedListADT<ItemType>::clear(){
   return ListADT<ItemType>::clear();
}

template<class ItemType>
ItemType SortedListADT<ItemType>::getEntry(int position) const throw(std::out_of_range) {
   return ListADT<ItemType>::getEntry(position);
}

template<class ItemType>
int SortedListADT<ItemType>::getPosition(const ItemType& entry)
{
   int position = 1;
   int length = getLength();
    
   while ( (position <= length) && (entry > getEntry(position)) ) {
      position++;
   }  // end while
    
   if ( (position > length) || (entry != getEntry(position)) ) {
      position = -position;
   }  // end if
    
   return position;
}

template<class ItemType>
bool SortedListADT<ItemType>::contains(const ItemType& entry) {
   return ListADT<ItemType>::contains(entry);
}

template<class ItemType>
bool SortedListADT<ItemType>::loadList( string filename) {
   ifstream file(filename);
   
   if (file.is_open()) {
      ItemType n;
      
      while(file >> n) {
         insertSorted(n);
      }
    } else {
       cout <<"File not found!";
       return false;
    }
    
    file.close();
    return true;  
    
}

template<class ItemType>
void SortedListADT<ItemType>::displayList() const {
   cout << *this;
}

template<class ItemType>
bool SortedListADT<ItemType>::operator==(const SortedListADT<ItemType>& rhs) const
{
	return ListADT<ItemType>::operator==(rhs);
} // end of operator==


template<class ItemType>
SortedListADT<ItemType> SortedListADT<ItemType>::operator+(const SortedListADT<ItemType>& rhs) const
{
	// Create a new ListADT object initialized from the linked list nodes
	// found in lhs operand - this pointer refers to the current instance object, 
	// which for C++ operators is always the lhs operand
	SortedListADT<ItemType> concatList = SortedListADT<ItemType>(*this);
	
	// iterate through the nodes in the rhs operant and add these to the new
	// ListADT at the end of the list (getLength() + 1)
	for (ListNode<ItemType> *curPtr = rhs.headPtr; curPtr != nullptr; curPtr = curPtr->next)
		concatList.insertSorted(curPtr->item);

	// return the new ListADT that is concatenation of the lhs and rhs
	return(concatList);
} // end of operator++

template<class friendItemType>
ostream& operator<<(ostream& outStream, const SortedListADT<friendItemType>& outputList)
{
   for(int i = 1; i <= outputList.getLength(); i++){
      outStream << outputList.getEntry(i) << " ";
   }
   
   return outStream;
} // end of ostream operator<< 



#endif
