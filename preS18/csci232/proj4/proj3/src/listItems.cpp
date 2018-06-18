#include "listItems.h"
#ifndef LIST_ITEMS_IMP
#define LIST_ITEMS_IMP




   listItems::listItems(){}; // default constructor;
   
   listItems::listItems(const string cc, const int postalCode, 
						const string lastName, const string firstName,
						const vector<string> giftList){
	country = cc;
	post= postalCode;
	last = lastName;
	first = firstName;
	gifts = giftList;
		
} 

   void listItems::setCountry(string cc){
		country = cc;
   }

   void listItems::setPost(int postalCode){
        post = postalCode;
   
   }

   void listItems::setFirst(string firstName){
      first = firstName;
   }

   void listItems::setLast(string lastName){
      last = lastName;
   }

bool listItems::operator!=(const listItems entry){
   bool isTrue = true;
   if(entry.first.compare(first) && entry.last.compare(last) && entry.post == post 
	  && entry.country.compare(country) ){
	     isTrue = false;  
	     for(unsigned int i = 0; i < gifts.size(); i++)
	  		if(!gifts.at(i).compare(entry.gifts.at(i)) )
	  			isTrue = true;
		 
		 } 

   return isTrue;

}



//string setGift();

	string listItems::toString() const {
	
	   string output;
	   output += "Country: " + country[0] + country[1];
	   output += "Postal Code: " + post;
	   output += "Last Name: " + last;
	   output += "First Name: " + first;
	   output += "\n";
	   output += "Gifts: ";
	   for(unsigned int i = 1; i <= gifts.size(); i++){
		 output += gifts.at(i);
	   }//end for
	
	return output;
	}


#endif