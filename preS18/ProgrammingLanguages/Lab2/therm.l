/* Nathaniel Lewis
 * Lab 2 Programming Languages
 */


%{
#include <stdlib.h>
void yyerror(char *);
#include "y.tab.h"
%}		

HEAT		(heat\ |HEAT\ |Heat\ )

ON			(on|ON|On)

OFF			(OFF|Off|off)

TEMP		(temperature|TEMPERATURE|Temperature|TEMP|temp|Temp)
				
HUMID		(humidity|HUMIDITY|Humidity)

EXIT		EXIT|exit|Exit|quit|Quit|QUIT

INT			[0-9]{2}



%%

		/* Turn heater on */
{HEAT}{ON}			{
						return ON;
					}
		/* Turn heater off */
{HEAT}{OFF}			{
						return OFF;
					}
		/* Target Temp */
{TEMP} 				{
						return TEMP;
					}
		/* Target Humidity*/		
{HUMID} 			{
						return HUMID;
					}
		/* Exit the program */
{EXIT}				{
						exit(1);
					}
		/* Sends value to Temp/Humidity */
{INT}				{
						yylval = atoi(yytext);
						return INT;
					}
[\n]				{ return *yytext; }
					
[ \t]		/* ignore white space */

.					yyerror("Invalid character");

%%

int yywrap (void) {
	return 1;
}


				