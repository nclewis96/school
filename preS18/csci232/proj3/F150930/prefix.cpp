/** @file prefix.cpp
 * Write a routine to recognize 
 * all prefix expressions given the 
 * following grammar:
 *
 * <prefix> := <identifier> | <operator> <prefix> <prefix>
 * <operator> := + | - | * | /
 * <identifier> := a | b | c | ... | z
 *
 */

#include <iostream>

using namespace std;

// Determine if the provided character is 
// a valid operator given the above grammar
bool isOperator(const char ch)
{
   string operators = "+-*/";
   return(operators.find(ch) != string::npos);
}

// Determine if the provided character is 
// a valid identifier given the above grammar
bool isIdentifier(const char ch)
{
   string identifiers = "abcdefghijklmnopqrstuvwxyz";
   return(identifiers.find(ch) != string::npos);
}


// Determine the index into the string expression
// that ends the prefix operation (1 operator and 2 operands)
int endPre(int first, const string expression)
{
   int last = expression.length() - 1;
   char ch;

   // If the first character is out of range
   if ( (first < 0) ||
        (first > last) )
      return(-1);

   ch = expression[first];
   if (isIdentifier(ch)) 
      return(first);
   else if (isOperator(ch))
   {
      int firstEnd = endPre(first + 1, expression);
      if (firstEnd > -1)
         return(endPre(firstEnd + 1, expression));
      else
         return(-1); 
   }
   else
      return(-1);
}

// Determine if a given string representing an expression is 
// a prefix expression
bool isPre(const string expression)
{
   int lastChar = endPre(0, expression); // Returns the index of end
   return( (lastChar >= 0) &&
           (lastChar == expression.length() -1) );
}

//
// Test Driver
// 
int main()
{
   // test some string expressions
   string expressions[] = { "*+abc", 	// true
                            "/-+abde",	// true
                            "+ac",	// true
                            "-acd",	// false
                            "/^ab",	// false
                            "-a",	// flase - no unary ops
			    "b" };	// true

    // loop through expressions and test to see if part of
    // out language represented by the grammar provided
    for (int idx = 0; idx < sizeof(expressions)/sizeof(expressions[0]); idx++)
       cout << "Testing the expression: " << expressions[idx] << endl
            << "Is this expression a prefix algebraic expression: "
            << isPre(expressions[idx]) << endl << endl;

    return(0);
}

