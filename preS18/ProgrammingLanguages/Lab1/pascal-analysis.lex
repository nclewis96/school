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
	int char_count = 1;
%}

DIGIT		[0-9]

ID			[a-z][a-z0-9]*

KEYWORD		if|then|begin|end|procedure|function

OPERATOR	"+"|"-"|"*"|"/"

WHITESP		[ \t]+

LINECOMMENT	("//".*)|("/*"([^*]|\*+[^*/])*\*+"/")|"{"[\^{}}\n]*"}"

TERMINAL	"=+="

%%

{DIGIT}+	{
				printf("integer(%s,%d)\n", yytext, atoi(yytext));
				char_count += yyleng;
            }
			
{DIGIT}+"."{DIGIT}*	{
				printf("float(%s,%f)\n", yytext, atof(yytext));
				char_count += yyleng;
			}
			
{KEYWORD}	{
				printf("keyword(%s)\n", yytext);
				char_count += yyleng;
			}
			
{ID}		{
				printf("identifier(%s)\n", yytext);
				char_count += yyleng;
			}
			
{OPERATOR}	{
				printf("operator(%s)\n", yytext);
				char_count += yyleng;
			}
			
{TERMINAL}  {
				exit(0);
			}

{LINECOMMENT}	{
					char_count += yyleng;
				}


{WHITESP}		{
					char_count += yyleng;
				}

\n			{
				++num_lines;
				char_count = 1;
			}

.			{
				printf("L%d, Col%d:Unrecognized token(%s)\n", num_lines, char_count, yytext);
				char_count += yyleng;
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
