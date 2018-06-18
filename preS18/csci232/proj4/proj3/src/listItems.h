#ifndef LIST_ITEMS
#define LIST_ITEMS

//#include "ListADT.h"
#include <string>
#include <vector>
using namespace std;



 class listItems
{
public:
   listItems();

   listItems(const string cc, const int postalCode, 
						const string lastName, const string firstName,
						const vector<string> giftList);
						
   void setCountry(string cc);

   void setPost(int postalCode);

   void setFirst(string firstName);

   void setLast(string lastName);

   //void setGift();

   string toString() const;

   bool operator!=(const listItems entry);

private:


   string country;

   int post;

   string first;

   string last;

   vector<string> gifts;
};
#endif