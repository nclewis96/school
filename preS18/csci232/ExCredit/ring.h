// Nathaniel Lewis
//nlewis
//nlewis


#ifndef _RING
#define _RING

#include "ringinterface.h";

template<class ItemType>
class Ring {

   private:
	 static const int DEFAULT_RING_SIZE = 6;  
	 ItemType items[DEFAULT_RING_SIZE]; // array of ring items
     int itemCount;                     // current count of ring items 
     int maxItems;                      // max capacity of the ring
     int refer;	                        // reference point for the array
     int contains(const ItemType& item);// checks if an item is inside it
  
   public:
    ItemType& getCurrent();             //Returns the current item
    //moves the reference down the list, or to the top if at the end
    void advance();
    bool addItem(const ItemType& item); //adds an item to the ring
    bool removeItem(const ItemType& item);//removes item from the list
	





} // End Ring

#include ring.cpp

#endif