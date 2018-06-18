/**
 * ListADT: Linked List Implementation
 * Nathaniel Lewis
 * nlewis
 * nlewis
 */
#ifndef _LISTADT
#define _LISTADT

#include "ListInterface.h"
#include "Node.h"
#include <stdexcept>
#include <vector>
#include <sstream>
#include <string>

using namespace std;


template<class ItemType>


class ListADT: public ListInterface<ItemType>
{



private:
	
	int itemCount;
	
	Node<ItemType>* headPtr;
	
	bool swap(int positionA, int positionB);
	
	bool replace(int position, const ItemType& newEntry);
	
	void reverse();
	
	 Node<ItemType>* getNodeAt(int position);
	 
	 vector<string> splitString(string str, char delim) const;
	
public:
	
	ListADT();
	
	~ ListADT();
	
	bool isEmpty() const;
	
	int getLength() const;
	
	bool insert(int newPosition, const ItemType& newEntry);
	
	bool remove(int position);
	
	void clear();
	
	Node<ItemType>* getEntry(int position) throw (logic_error);
	
	void setEntry(int position, const ItemType& newEntry) throw (logic_error);
	
	int getPosition(const ItemType& entry);
	
	bool contains(const ItemType& entry);
	
	bool loadList(const string filename);
	
	void displayList();
	

};

#include "ListADT.cpp"
#endif