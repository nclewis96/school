/** @file GoodMemory.cpp */
#include "GoodMemory.h"

GoodMemory::GoodMemory ():someBoxPtr (nullptr)
{
}				// end default constructor

GoodMemory::~GoodMemory ()
{
  delete someBoxPtr;
}				// end destructor

void
GoodMemory::fixedLeak (const double &someItem)
{
  someBoxPtr = new ToyBox < double >();

  someBoxPtr->setItem (someItem);
}				// end fixedLeak

