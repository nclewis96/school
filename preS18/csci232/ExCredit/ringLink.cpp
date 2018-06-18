// Nathaniel Lewis
//nlewis
//nlewis

//Most of these methods are unfinished and do not work.


#include "ring.h, node.cpp"

template<class ItemType>
ringLink<ItemType>::ringLink() : itemCount(0)
{
}  // end default constructor

template<class ItemType>
ItemType& getCurrent()
{
    return curPtr->getItem();
}

template<class ItemType>
void advance() 
{
   if(curPtr->getNext()->getItem() != nullptr)
     curPtr = curPtr->getNext();
   return;
}

template<class ItemType>
bool addItem(const ItemType& item)
{
   bool itemAdded = false;
   if(curPtr->getNext() == nullptr)
   {
      curPtr->setNext(new Node(item))
   }
   
   
   
   return itemAdded;
}

//
template<class ItemType>
bool removeItem(const ItemType& item)
{
	bool isRemoved = false;
	Node* toDel = containsNode(item)
	if(toDel != nullptr)
	{
		toDel
	}
		
      
      
      
   
   return isRemoved;
}

template<class ItemType>
Node* containsNode(const ItemType& item)
{
   Node *loopPtr = new Node();
   loopPtr = curPtr;
   while(loopPtr->getItem() != item){
        loopPtr->setNext(loopPtr->getNext());
        if(loopPtr == curPtr)
        	return nullptr;
   }
   
   return loopPtr;
   
}
