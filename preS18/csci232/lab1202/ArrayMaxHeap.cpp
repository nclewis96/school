//Nathaniel Lewis
//nlewis
//nlewis

#ifndef _ARRAY_MAX_HEAPIMP
#define _ARRAY_MAX_HEAPIMP

#include "ArrayMaxHeap.h"
#include "HeapInterface.h"
#include "math.h"

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

//Public methods

template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap(){
   itemCount = 0;
   maxItems = DEFAULT_CAPACITY;
   items = new ItemType[maxItems];
}//end Default constructor

template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap(const ItemType someArray[], const int arraySize):
itemCount(arraySize), maxItems(2 * arraySize)
{
// Allocate the array
items = new ItemType[2 * arraySize];
// Copy given values into the array
for (int i = 0; i < itemCount; i++)
 items[i] = someArray[i];

// Reorganize the array into a heap
heapCreate();
} // end constructor

template<class ItemType>
ArrayMaxHeap<ItemType>::~ArrayMaxHeap(){
   clear();
}//end destructor

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const{
	return itemCount == 0;
}//end isEmpty

template<class ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const{
   return itemCount;
}//end getNumberOfNodes

template <class ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const{
   return ceil(log2(itemCount + 1));
}//end getHeight

template <class ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const throw (logic_error) {
   if (isEmpty())
      throw logic_error("Attempted peek into an empty heap.");
   return items[0];
}//end peekTop

template<class ItemType>
bool ArrayMaxHeap<ItemType>::add(const ItemType& newData){
   bool canAdd = maxItems > itemCount;
   items[itemCount] = newData;
   int place = itemCount;
   int parent = ( place - 1 ) / 2;
   
   while( parent >= 0 && items[place] > items[parent]) {
      ItemType temp = items[parent];
      items[parent] = items[place];
      items[place] = temp;
      place = parent;
      parent = (place - 1) / 2;
   }
   
   itemCount++;
   return canAdd;
}//end add

template<class ItemType>
bool ArrayMaxHeap<ItemType>::remove(){
	if(!isEmpty()) {
	   ItemType toSwitch = items[itemCount - 1];
	   items[0] = toSwitch;
	   items[itemCount] = 0;
	   heapRebuild(0);
	   itemCount--;
	   return true;
	}else {
	   return false;
	}
	
}//end remove

template<class ItemType>
void ArrayMaxHeap<ItemType>::clear(){
   for(int i = 0; i < itemCount; i++)
      items[i] = 0;
    itemCount = 0;
}//end clear

//Private Methods

template<class ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const{
   int leftIndex = (2 * nodeIndex) + 2;
   if(leftIndex >= maxItems)
      leftIndex = -1;
   return (leftIndex);
}//end getLeftChildIndex

template<class ItemType>
int ArrayMaxHeap<ItemType>::getRightChildIndex(int nodeIndex) const{
   int rightIndex = (2 * nodeIndex) + 2;
   if(rightIndex >= maxItems)
      rightIndex = -1;
   return (rightIndex);
}//end getRightChildIndex

template<class ItemType>
int ArrayMaxHeap<ItemType>::getParentIndex(int nodeIndex) const{
	if(nodeIndex % 2  == 0){
		return  (nodeIndex - 2) / 2;
	}else {
	    return  (nodeIndex - 1) / 2;
	} 
}//end getParentIndex

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isLeaf(int nodeIndex) const{
 if(getRightChildIndex(nodeIndex) == -1 && getLeftChildIndex(nodeIndex) == -1)
    return true;
 else 
    return false;
}//end isLeaf


template<class ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild (int subTreeRootIndex) {

// Recursively trickle the item at index root down to its proper position by 
// swapping it with its larger child, if the child is larger than the item.
// If the item is at a leaf, nothing needs to be done.
   int child = getLeftChildIndex(subTreeRootIndex);
   if (child < itemCount){
      int rightChild = getRightChildIndex(subTreeRootIndex);
      // The root must have a left child; assume it is the larger child largerChildIndex = 2 * rootIndex + 1 //Leftchildindex
      if (rightChild < itemCount && items[rightChild] > items[child] ) {
         child = rightChild;
      }

	   
      // If the item in the root is smaller than the item in the larger child, swap items
     if (items[subTreeRootIndex] < items[child]){
        ItemType swap = items[subTreeRootIndex];
        items[subTreeRootIndex] = items[child];
        items[child] = swap;
        heapRebuild(child); 
     }

    }// Else root is a leaf, so you are done

}//end heapRebuild

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapCreate(){
    for (int index = (itemCount / 2); index >= 0; index--)
       heapRebuild(index);
}//end heapCreate



#endif



