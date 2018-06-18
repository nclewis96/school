/** @file NotFoundException.cpp */
#include "NotFoundException.h"  

NotFoundException::NotFoundException(const string& message)
         : logic_error("Not Found Exception: " + message)
{
}  // end constructor

// End of implementation file.

