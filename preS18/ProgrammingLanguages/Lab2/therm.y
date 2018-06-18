/* Nathaniel Lewis
 * Lab 2 Programming Languages
 */

%{
	#include <stdio.h>
	int yylex(void);
	int pwr, temp, hum;
	void yyerror(char *);
%}

%token INT TEMP HUMID ON OFF HEAT

%%

program: 
		program cmd '\n'
		|
		;
		
cmd:
		/* Turn heater on */
		ON 					{ 
								pwr = 1; 
								printf("Heater is now on.\n");
							}
		/* Turn heater off */
		| OFF				{ 
								pwr = 0; 
								printf("Heater is now off.\n");
							}
		/* Check heaters status, then if the temp is in the correct range */
		| TEMP INT			{ 	if(pwr == 1 && $2 > 45 && $2 < 85 ) {
									temp = $2;
									printf("Temperature has been set to %d\n", temp);  
								}else if ( pwr == 0){
									printf("Temperature cannot be set, heat is off\n");
								}else {
									printf("Temperature is out of range, please set between 45-85˚\n");
								}
							}
		/* Check heaters status, then if the Humidity is in the correct range */
		| HUMID	INT			{  
								if(pwr == 1 && $2 > 35 && $2 < 75 ) {
									hum = $2;
									printf("Humidity has been set to %d\n", hum);  
								}else if ( pwr == 0){
									printf("Humidity cannot be set, heat is off\n");
								}else {
									printf("Humidity is out of range, please set between 35-75˚\n");
								}
							}
		;

		
		
		
%%


void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}

int main(void) {
	yyparse();
	return 0;
}

