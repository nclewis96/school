/*
 * 
 *@file postfix.cpp
 * Write a routine to recognize 
 * all postfix expressions given the 
 * following grammar:
 *
 * <postfix> := <identifier> | <postfix> <postfix> <operator>
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
// that ends the postFix operation (2 operands and 1 operator)
int endPost(int first, const string expression)
{
    int last = expression.length() - 1;
    char ch;
    
    //make sure that the position is inside the string
    if( first < 0 || first > last) 
       return -1;
    
    
    //Identifies what it is, decides what to do
    ch = expression[first];
    
    
    
    
    if( isIdentifier(ch) ) 
    {
       if(expression.length() == 1)
         return first;
         
       // if the next char is an identifier that is at the end of the code
       // and is followed by another identifier return itself
       int firstEnd = endPost(first + 1, expression);
       if(firstEnd  == last && isIdentifier(expression[firstEnd - 1]) && last > 1)
         return firstEnd;
       else if (firstEnd > -1 )
       	 return endPost(firstEnd + 1, expression);
       else  
         return -1;
       
       
    }  
    else if( isOperator(ch) ) 
      return first;
    else 
      return -1;
    //end if
    
    
}

// Determine if a given string representing an expression is 
// a postfix expression
bool isPost(const string expression)
{
   int lastChar = endPost(0, expression);
   return(lastChar >= 0 && lastChar == expression.length() - 1 );
}

//
// Test Driver
// 
int main()
{
   // test some string expressions
   string expressions[] = { "ab+c*", 	// true
                            "ab/d-e+",	// true
                            "ac+",		// true
                            "ac-d",		// false
                            "ab/+",		// false
                            "a-",		// false - no unary ops
                            "d" };		// true

    // loop through expressions and test to see if part of
    // out language represented by the grammar provided
    for (int idx = 0; idx < sizeof(expressions)/sizeof(expressions[0]); idx++)
       cout << "Testing the expression: " << expressions[idx] << endl
            << "Is this expression a postfix algebraic expression: "
            << isPost(expressions[idx]) << endl << endl;

    return(0);
}

