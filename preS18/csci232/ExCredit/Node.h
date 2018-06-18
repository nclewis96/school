// Nathaniel Lewis
//nlewis
//nlewis

#ifndef _NODE
#define _NODE


template<class ItemType>
class Node {

   private:
	 ItemType& item; // what the node will contain
	 Node *node; // what the node will point at
  
   public:
    ItemType& getItem();             //returns the current item
    //sets what Node the current Node points at
    void setNext(const Node n);
    Node* getNext; //returns the Node the current one points at
    void setItem(const ItemType& item); // sets what item the node holds
	





} // End Node

#include Node.cpp

#endif