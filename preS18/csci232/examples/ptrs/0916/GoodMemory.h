/** @file GoodMemory.h */
#include 
#include "ToyBox.h"
using namespace std;

class GoodMemory
{
  private:ToyBox < string > *someBoxPtr;

  public:GoodMemory ();	// Default constructor

  ~GoodMemory ();	// Destructor

  void fi xedLeak (const double &someItem);

};  // end GoodMemory

