/*
 * Simple Lexical Analyzer that recognizes Email Addresses
 * F17 CSCI 305 Programming Languages - Lab 01
 * 2016-08-26
 * Phillip J. Curtiss
 * Version 0.1
 */

EMAIL	^([a-z0-9_\.-]+)@([a-z0-9_\.-]+)\.([a-z\.]{2,6})$

%%

{EMAIL}    {
	        printf("Found an E-Mail Address: %s\n", yytext);
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
