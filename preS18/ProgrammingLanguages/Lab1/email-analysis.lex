/*
 * Simple Lexical Analyzer that recognizes Email Addresses
 * F17 CSCI 305 Programming Languages - Lab 01
 * 2016-08-26
 * Phillip J. Curtiss
 * Version 0.1
 */

EMAIL	([a-z0-9_\.-]+)@([a-z0-9_\.-]+)\.([a-z\.]{2,6})

PHONE	([0-9]{3})\-?([0-9]{4})

LONG	\(?([2-79][0-9]{2})|(8((0[1-9])|(6[1-57-9])|(7[1-689])|(8[1-79])))?\-?

TLLFREE	\(?8(00|66|77|88)\)?\-?
        
ZIP		([0-9]{5})(\+([0-9]{4}))?






%%

{EMAIL}    {
	        printf("Found an E-Mail Address: %s\n", yytext);
            }
            
{TLLFREE}{PHONE}	{
			 printf("Found a Toll Free Number: %s\n", yytext);
			 }
			 
{LONG}{PHONE}	{
			 printf("Found a Long Distance Number: %s\n", yytext);			 
             }
             
{PHONE}		{
			 printf("Found a Local Number: %s\n", yytext);
			 }

{ZIP}		{
			 printf("Found a Zip Code: %s\n", yytext);
			 }
            

%%

int main(int argc, char **argv) 
{
    ++argv, --argc; /* skip over program name */

    if (argc > 0)
       yyin = fopen(argv[0], "r");
    else
       yyin = stdin;

    yylex();
}
