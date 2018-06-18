/** @file infixParen.cpp
 * Write a routine to recognize 
 * all infix expressions with parens given the 
 * following grammar:
 *
 * <infix> := <identifier> | ( <infix> <operator> <infix> )
 * <operator> := + | - | * | /
 * <identifier> := a | b | c | ... | z
 *
 *Name Nathaniel Lewis
 *Katie User nlewis
 *User nlewis
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
// that ends the inFix operation (1 operand 1 operator 1 operand)
// with parens
int endInfix(int first, const string expression)
{
int last = expression.length() - 1;
   char ch;

   // If the first character is out of range
   if ( (first < 0) || (first > last) )
      return(-1);
   
   int firstEnd;
   ch = expression[first];
   
   //determines whether or not it's the last paren
   if(expression[first] == ')' ){
   	  if( first == last)
   	   return first;
   	  else
   	  	return endInfix(first + 1, expression);
   }
   else if (expression[first] == '(' ){
       return endInfix(first + 1, expression);	
   }
   //decides what to do with an identifier, makes sure it follows the grammar
   else if ( isIdentifier(ch) )
   {
  	  if(isOperator(expression[first -1]) || expression[first - 1] == '(' )
  	  	return endInfix(first + 1, expression);
      else if(first == last && first == 0)
        return(first);
      else 
        return - 1;
   }     
   //decides if an operator follows the grammar
   else if (isOperator(ch))
   {
      if( (isIdentifier(expression[first - 1]) || expression[first - 1] == ')' ) &&
      	(isIdentifier(expression[first + 1]) || expression[first + 1] == '(') )
        return endInfix(first + 1, expression);
   }
   

}

// Determine if a given string representing an expression is 
// a postfix expression
bool isInfix(const string expression)
{
   int lastChar = endInfix(0, expression);
   return(lastChar >= 0 && lastChar == expression.length() - 1 );
}

//
// Test Driver
// 
int main()
{
   // test some string expressions
   string expressions[] = { "a",	 	// true
                            "(a-e)",		// true
                            "(a+c)+(b-c)",// true
                            "(a*(a-d))",	// true
                            "a+(b/c)",	// false
                            "a+b" };		// false

    // loop through expressions and test to see if part of
    // out language represented by the grammar provided
    for (int idx = 0; idx < sizeof(expressions)/sizeof(expressions[0]); idx++)
       cout << "Testing the expression: " << expressions[idx] << endl
            << "Is this expression a infix with parens algebraic expression: "
            << isInfix(expressions[idx]) << endl << endl;

    return(0);
}

