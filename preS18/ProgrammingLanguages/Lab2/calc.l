/* Nathaniel Lewis
 * Lab 2 Programming Languages
 */

%{
#include <stdlib.h>
void yyerror(char *);
#include "y.tab.h"
%}		

%%

	/* Variables */ 
[a-z]		{
				yylval = *yytext - 'a';
				return VARIABLE;
			}

	/* Registers */
R[0-9]		{
				yylval = *yytext - 'a';
				return REGISTER;
			}

	/* integers */
[0-9]+		{
				yylval = atoi(yytext);
				return INTEGER;
			}
		
[-+()=/*\n]	{	return *yytext;	}

[ \t]		; /* skip whitespace */

.			yyerror("invalid character");

%%

int yywrap (void) {
	return 1;
}