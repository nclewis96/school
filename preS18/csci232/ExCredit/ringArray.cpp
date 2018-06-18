// Nathaniel Lewis
//nlewis
//nlewis


#include "ring.h"

template<class ItemType>
ringArray<ItemType>::ringArray() : itemCount(0), maxItems(DEFAULT_BAG_SIZE)
{
}  // end default constructor

template<class ItemType>
ItemType& getCurrent()
{
    return itemCount;
}

template<class ItemType>
void advance() 
{
   refer++;
   if(refer >= maxItems)
   	  refer = 0;
   return;
}

template<class ItemType>
bool addItem(const ItemType& item)
{
   if(itemCount == maxItems)
      return false;
	items[refer] = item;
	itemCount++;
	refer++;
	return true;
}

template<class ItemType>
bool removeItem(const ItemType& item)
{
   int remove = contains(item);
   bool isRemoved = false;
   if(remove < maxCount)
   {
	  items[remove] = null;
   }
   return isRemoved;
}

template<class ItemType>
int contains(const ItemType& item)
{
   int isContained = -1;
   for(int i = 0; i < maxCount; i++)
   {
       if(item == items[i])
       {
          isContained = i;
       }
   }
   return isContained;
}
