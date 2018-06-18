/** ADT bag: Link-based implementation.
@file LinkedBag.h */
#ifndef _LINKED_BAG
#define _LINKED_BAG

#include "BagInterface.h"
#include "ListNode.h"
#include <ostream>
#include <iostream>
using namespace std;

template<class ItemType> 
class LinkedBag:public BagInterface<ItemType>
{
private:
  ListNode<ItemType>* headPtr;	// Pointer to first node
  int itemCount;		// Current count of bag items
  ListNode<ItemType>* getNext(ListNode<ItemType>* n)const; 
  ItemType getItem(ListNode<ItemType>* n)const;
// Returns either a pointer to the node containing a given entry
// or the null pointer if the entry is not in the bag.
  ListNode<ItemType>* getPointerTo(const ItemType& target) const;

public:
  LinkedBag();
  LinkedBag(const LinkedBag<ItemType>& aBag); // Copy constructor
  virtual ~ LinkedBag();	// Destructor should be virtual
  int getCurrentSize() const;
  bool isEmpty() const;
  bool add(const ItemType& newEntry);
  bool remove(const ItemType& anEntry);
  void clear();
  bool contains(const ItemType& anEntry) const;
  int getFrequencyOf(const ItemType& anEntry) const;
  std::vector<ItemType> toVector() const;
  bool operator==(const LinkedBag<ItemType>& rhs) const;
  LinkedBag<ItemType> operator+(const LinkedBag<ItemType>& rhs) const;
  
  template<class friendItemType>
  friend std::ostream& operator<<(std::ostream& outputStream, 
                                  const LinkedBag<friendItemType>& outputList);
};  // end LinkedBag

#include "LinkedBag.cpp"
#endif
