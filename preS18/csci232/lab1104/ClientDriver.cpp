//-----------------------
// Using statements
//-----------------------
using namespace std;
 
//-----------------------
// C++ includes
//-----------------------
#include <iostream>
#include <fstream>
#include <string>

//-----------------------
// Application includes
//-----------------------
#include "LinkedBag.cpp"

int main() {

   LinkedBag<string> L1 = LinkedBag<string>();
   LinkedBag<string> L2 = LinkedBag<string>();
   LinkedBag<string> L3 = (L1 + L2);
   
   L1.add("Hello");
   L1.add("World");
   L1.add("Fubar");
   L2.add("Hello");
   L2.add("World");
   L2.add("Fubar");
   
   bool l1l2 = (L1 == L2);
   bool l1l3 = (L1 == L3);
   bool l2l3 = (L2 == L3);
   bool l3l3 = (L3 == L3);
   
   cout<< " Is L1 equal to L2? " << l1l2 << endl;
   cout<<"------------------------------------------" << endl;
   cout<< " Is L1 equal to L3? " << l1l3 << endl;
   cout<<"------------------------------------------" << endl;
   cout<< " Is L2 equal to L3? " << l2l3 << endl;
   cout<<"------------------------------------------" << endl;
   cout<< " Is L3 equal to L3? " << l3l3 << endl;
   cout<<"------------------------------------------" << endl;
   cout<<endl;
   cout<<"L1 contains: \n" << L1 << endl;
   cout<<endl;
   cout<<"L2 contains: \n" << L2 << endl;
   cout<<endl;
   LinkedBag<string> L4 = L1 + L1;
   cout<<"L3 contains: \n" << L3 << endl;
   
   
   return 0;
}