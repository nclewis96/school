/*
 * Simple Lexical Analyzer that recognizes pascal language constructs
 * F17 CSCI 305 Programming Languages - Lab 01
 * 2016-08-26
 * Phillip J. Curtiss
 * Version 0.1
 */
%{ /* Needed for calls from math lib (e.g. atof) */
	#include <math.h>
	
	int num_lines = 1;
%}

DIGIT		[0-9]

ID			[a-z][a-z0-9]*

KEYWORD		if|then|begin|end|procedure|function

OPERATOR	"+"|"-"|"*"|"/"

WHITESP		[ \t]+

LINECOMMENT	"{"[\^{}}\n]*"}"

%%

{DIGIT}+	{
				printf("integer(%s,%d)\n", yytext, atoi(yytext));
            }
			
{DIGIT}+"."{DIGIT}*	{
				printf("float(%s,%f)\n", yytext, atof(yytext));
			}
			
{KEYWORD}	{
				printf("keyword(%s)\n", yytext);
			}
			
{ID}		{
				printf("identifier(%s)\n", yytext);
			}
			
{OPERATOR}	{
				printf("operator(%s)\n", yytext);
			}

{LINECOMMENT}	/* Do nothing, just consume input */

{WHITESP}		/* Do nothing, just consume input */

\n			{
				++num_lines;
			}

.			{
				printf("L%d:Unrecognized token(%s)\n", num_lines, yytext);
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
