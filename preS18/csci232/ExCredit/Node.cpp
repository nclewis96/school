// Nathaniel Lewis
//nlewis
//nlewis

#include "Node.h"

emplate<class ItemType>
Node<ItemType>*::Node() : 
{
}  // end default constructor

template<class ItemType>
ItemType& getItem() 
{
	return item;

}


template<class ItemType>
Node* getNext()
{
	return node;
}



template<class ItemType>
void setNext(Node* n)
{
	node = n;
	return;
}


template<class ItemType>
void setItem(ItemType& i)
{
	item = i;
	return;
}
