/** @file palindrome.cpp
 * Write a routine to recognize 
 * all palindrome expressions given the 
 * following grammar:
 *
 * <pal> := emptyString | <ch> | <ch> <pal> <ch>
 * <ch> := a | b | c | ... | z | A | B | ... | 
 *
 *Name Nathaniel Lewis
 *Katie User nlewis
 *User nlewis
 */

#include <iostream>

using namespace std;

// Is the string a palindrome expression
bool isPalindrome(const string expression)
{
	// if (expression is the empty string or of length 1)
        //    return true;
        // else if (expression's first and last characters are the same)
        //    return isPalindrome(expression minus its first and last char)
        // else 
        //    return false
    int first = 0;
    int last = expression.length() - 1;
    
    //checks if both sides of the string are the same, then gets rid of those chars
    if(expression.length() <= 1){
       return true;
        
    } else if(expression[first] ==(expression[last])){
       return isPalindrome(expression.substr(first + 1, last - 1));
    } else {
       return false;
    } // end if
        
        
	
}


//
// Test Driver
// 
int main()
{
   // test some string expressions
   string expressions[] = { "radar", 	// true
                            "pip",	// true
                            "pirrip",	// true
                            "fancy",	// false
                            "ada",	// true
                            "fooboof",	// true
			    "b",	// true
			    "baabaa",	// false
                            "" };	// true

    // loop through expressions and test to see if part of
    // out language represented by the grammar provided
    for (int idx = 0; idx < sizeof(expressions)/sizeof(expressions[0]); idx++)
       cout << "Testing the expression: " << expressions[idx] << endl
            << "Is this expression a palindrome expression: "
            << isPalindrome(expressions[idx]) << endl << endl;

    return(0);
}

