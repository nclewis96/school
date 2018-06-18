/**
 * Implementation
 * Nathaniel Lewis
 * nlewis
 * nlewis
 */
#ifndef _LISTADTIMP
#define _LISTADTIMP

#include "ListInterface.h"
#include "ListADT.h"
#include "listItems.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
 

template<class ItemType>
ListADT<ItemType>::ListADT() {
	headPtr = nullptr;
   itemCount = 0;
   
}

template<class ItemType>
ListADT<ItemType>::~ListADT(){
	clear();
}

template<class ItemType>
bool ListADT<ItemType>::isEmpty() const { 
   return getLength() == 0;
      
}

template<class ItemType>
int ListADT<ItemType>::getLength() const { 
   return itemCount;
}

template<class ItemType>
bool ListADT<ItemType>::insert(int newPosition, const ItemType& newEntry) {
   bool canInsert = (newPosition >=1) && (newPosition <= getLength() );
   
   if(canInsert){
      Node<ItemType>* newPtr = new Node<ItemType>(newEntry);
      
      if(getLength() == 1){
         newPtr -> setNext(headPtr);
         headPtr = newPtr;
         
      }//end if
      else{
         Node<ItemType>* prev = getNodeAt(newPosition );
         newPtr -> setNext(prev->getNext());
         prev -> setNext(newPtr);
      
      }//end else 
   
      itemCount++;
   }//end if
 return canInsert; 
}

template<class ItemType>
bool ListADT<ItemType>::remove(int position){
   bool canRemove = (position >= 1 && position <= getLength() );
   if(canRemove) {
      Node<ItemType>* curPtr = nullptr;
      if(position == 1) {
         curPtr = headPtr;
         headPtr = headPtr -> getNext();
         
      }//end if
      else {
         Node<ItemType>*prevPtr = getNodeAt(position - 1);
         curPtr = getNodeAt(position);
         prevPtr -> setNext(curPtr -> getNext());
         
      }//end else
      curPtr -> setNext(nullptr);
      delete curPtr;
      curPtr = nullptr;
      itemCount--;
      
   }//end if
   
   return canRemove;
}


template<class ItemType>
Node<ItemType>* ListADT<ItemType>::getEntry(int position) throw (logic_error){
   Node<ItemType>* nPtr = getNodeAt(position);
   if(nPtr == nullptr)
      throw logic_error("The given position is not in the list.");
      
   return nPtr; 
}

template<class ItemType>
void ListADT<ItemType>::setEntry(int position, const ItemType& newEntry) throw (logic_error)
{
   if(!replace(position, newEntry))
      throw logic_error("The given position is not in the list.");
   return;
}

template<class ItemType>
bool ListADT<ItemType>::swap(int positionA, int positionB){ 
   bool canSwap =  (positionA >= 1 && positionA <= getLength() ) &&
                   (positionB >= 1 && positionB <= getLength() ) ;
                  
   if(canSwap){
      Node<ItemType>* A = getNodeAt(positionA);
      Node<ItemType>* B = getNodeAt(positionB);
      Node<ItemType>* helper = new Node<ItemType>;
      helper -> setItem(A -> getItem());
      
      A -> setItem(B -> getItem());
      B -> setItem(helper -> getItem());
         
      
      helper -> setNext(nullptr);
      delete helper;
      helper = nullptr;
   }//end if              

   return canSwap;
}
	
template<class ItemType>
void ListADT<ItemType>::reverse() {

   for(int i = 0; i < getLength()/2; i++){
   	  if(i + 1 != getLength() - i)
         swap(i + 1, getLength() - i);
   }


}

template<class ItemType>
bool ListADT<ItemType>::replace(int position, const ItemType& newEntry) { 

   bool canReplace = ( position >= 1 && position <= getLength() );
   if(canReplace){
      Node<ItemType>* nPtr = getNodeAt(position);
      nPtr -> setItem(newEntry);
      
   }
   
   return canReplace;
 }
 
 template<class ItemType>
 Node<ItemType>* ListADT<ItemType>::getNodeAt(const int position){
    Node<ItemType>* current = nullptr;
    if(position < 1 || position > getLength())
    	return current;
    for(int i = 0; i < position; i++){
       current = current -> getNext();
   }//end while
   
    
    return current;
 }
 
 template<class ItemType>
 void ListADT<ItemType>::clear(){
    while(!isEmpty())
		remove(1);
 }

template<class ItemType>
int ListADT<ItemType>::getPosition(const ItemType& entry) {
   Node<ItemType>* nPtr = headPtr;
   int counter = 1;
 
   while( (nPtr -> getItem() != entry) && (nPtr != nullptr) ){
       nPtr = nPtr -> getNext();
       counter++;
   }//end while
 
   //if the entry is not in the list, counter is greater than the length of the List.
   if(counter > getLength() || nPtr == nullptr){
      counter = -1;
   }//end if
 
   nPtr -> setNext(nullptr);
   delete nPtr;
   nPtr = nullptr;
 
   return counter;
}

template<class ItemType>
bool ListADT<ItemType>::contains(const ItemType& entry) { 
   bool contain = false;
   
   if(getPosition(entry) > 0)
      contain = true;

   return contain; 
}

template<class ItemType>
bool ListADT<ItemType>::loadList(const string filename) { 
   ifstream file;
	
   file.open(filename.c_str());
	
   if(file.is_open()) {
	  vector<string> words;
	  string line;
	  string country;
      int post;
	  string lName;
	  string fName;
	  vector<string> gifts;
		
	  //parses the strings into the different parts.
	  while(getline(file, line)) {
		  words = splitString(line, ' ');
		  country = words.at(1);
		  post = atoi(words.at(2).c_str());
		  lName = words.at(3);
		  fName = words.at(4);
		  for(unsigned int i = 5; i < words.size(); i++)
	      	gifts.push_back(words.at(i));
			
		  listItems child(country, post, lName, fName, gifts);
		  cout << child.toString() << endl;
			
			
		}		
	}
	file.close();
	return true; 

   
   return true; 
}


template<class ItemType>
void ListADT<ItemType>::displayList(){ 

   Node<ItemType>* curPtr = headPtr;
 
   while( curPtr ->getNext() != nullptr) {
     
      cout  << curPtr -> getItem() << endl;
      curPtr = curPtr -> getNext();
   }//end while

}

template <class ItemType>
vector<string> ListADT<ItemType>::splitString(string str, char delim) const {
	vector<string> vect;
	stringstream ss(str);
	string token;
	while(getline(ss, token, delim)) {
		vect.push_back(token);
	}
	
	return vect;
}

#endif
