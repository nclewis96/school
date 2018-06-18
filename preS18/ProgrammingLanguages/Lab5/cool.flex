/*	Nathaniel Lewis
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST ]; /* to assemble string constants */
char *string_buf_ptr;

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

/*
 *  Add Your own definitions here
 */
#define ERR(err) do { yylval.error_msg = err; return (ERROR); } while (0)
#define COND(cond, err) do { if (cond) ERR(err); } while (0)

#define string_buf_push(c) \
	COND(string_buf_ptr - string_buf >= MAX_STR_CONST, "String constant is too long"); \
	*string_buf_ptr++ = (c);

int ineof = 0;
int failstr = 0;
int nestedNum = 0;
%}

/*
 * Define names for regular expressions here.
 */


%x string
%x multiLineComment

LINECOMMENT --[^\n]*

INTEGER		[0-9]+

CLASS 		(?i:class)
ELSE		(?i:else)
FALSE		"f"(?i:alse)
FI			(?i:fi)
IF			(?i:if)
IN			(?i:in)
INHERITS	(?i:inherits)
ISVOID		(?i:isvoid)
LET			(?i:let)
LOOP		(?i:loop)
POOL		(?i:pool)
THEN		(?i:then)
WHILE		(?i:while)
CASE		(?i:case)
ESAC		(?i:esac)
NEW			(?i:new)
OF			(?i:of)
NOT			(?i:not)
TRUE		"t"(?i:rue)
TYPEID		[A-Z][a-zA-Z0-9_]*
OBJECTID	[a-z][a-zA-Z0-9_]*


WHITESPACE	[ \f\r\t\v]*

OPERATOR	[\+\-\*\/\=\{\}\@\,\;\:\~\.\(\)]

DARROW          =>
ASSIGN			<-
LE				<=
MULTICOMMENTSTART 	"(*"
MULTICOMMENTEND 	"*)"
NEWLINE				"\n"

%%

{WHITESPACE}	{						}
{NEWLINE}		{ curr_lineno++;		}

 /*
  *  Nested comments
  */
  
{LINECOMMENT} 	{						}

 /*
  * All multi line Comment code done by Kodi Neumiller
  */

{MULTICOMMENTSTART} {
						nestedNum++;
						BEGIN(multiLineComment);
					}
					
<multiLineComment>[^*\n\(]* { }
<multiLineComment>"*"[^\*\)\n]*   { }
<multiLineComment>\( { }

 /* increments the number of nested comments, prevents from going back to the initial
  * condition prematurely
  */
<multiLineComment>{MULTICOMMENTSTART} {
	nestedNum++;
}

<multiLineComment>{NEWLINE} {
	curr_lineno++;
}
<multiLineComment>{MULTICOMMENTEND} {
	nestedNum--;
	if (nestedNum == 0)
		BEGIN(INITIAL);
}
<multiLineComment><<EOF>> {
	BEGIN(INITIAL);
	ERR("End of File in Comment");
}

 /*
  *  The multiple-character operators.
  */
{DARROW}			{ return (DARROW); 		}
{ASSIGN}			{ return (ASSIGN); 		}
{LE}				{ return (LE);			}
{INTEGER}			{ yylval.symbol = inttable.add_string(yytext); return (INT_CONST); }
{MULTICOMMENTEND}	{ ERR("Unmatched *)");	}

 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */

{CLASS}			{ return (CLASS); 		}
{ELSE}			{ return (ELSE);  		}
{FI}			{ return (FI);    		}
{IF}			{ return (IF);    		}
{IN}			{ return (IN);	   		}
{INHERITS} 	    { return (INHERITS);	}
{ISVOID}		{ return (ISVOID);		}
{LET}			{ return (LET);   		}
{LOOP}			{ return (LOOP);		}
{POOL} 			{ return (POOL); 		}
{THEN} 			{ return (THEN);		}
{WHILE} 		{ return (WHILE);		}
{CASE}			{ return (CASE); 		}
{ESAC}			{ return (ESAC);		}
{NEW}			{ return (NEW);			}
{OF}			{ return (OF);			}
{NOT}			{ return (NOT); 		}

{TYPEID}		{ yylval.symbol = idtable.add_string(yytext); return (TYPEID);		}
{OBJECTID}		{ yylval.symbol = idtable.add_string(yytext); return (OBJECTID);	}
{OPERATOR}		{ return (*yytext);													}
{TRUE}			{ yylval.boolean = 1; 					      return (BOOL_CONST); 	}
{FALSE} 		{ yylval.boolean = 0; 		 		   	      return (BOOL_CONST);	}




 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  */



\"				{ string_buf_ptr = string_buf; failstr = 0; BEGIN(string); }

 /*
  * Ends the string and goes back to the initial condition so long as the string does not
  * end prematurely
  */
<string>(\"|\n)		{ 
						BEGIN(INITIAL); 
						if (failstr == 0)	{
							COND(*yytext == '\n', "Unterminated string constant");
							string_buf_push('\0');
							yylval.symbol = stringtable.add_string(string_buf);
							return (STR_CONST);
						}
					}

 /*
  * Checks all exceptions to escaped characters, and checks for null characters and EOF in 
  * the string.
  */
<string>\0		{ ERR("String contains null constant"); }
<string><<EOF>>	{ if (ineof) yyterminate(); ineof = 1; ERR("EOF in string constant"); }
<string>\\n		{ string_buf_push('\n'); 				}
<string>\\t		{ string_buf_push('\t'); 				}
<string>\\b		{ string_buf_push('\b'); 				}
<string>\\f		{ string_buf_push('\f'); 				}

 /*
  * adds most (except cases above) escaped characters to the string as just the character
  * without the '\'. Also allows for an escaped newline something like
  *"This \
  * is OK"
  */
<string>\\(.|\n)		{ 
						if (0 == yytext[1])
							failstr = 1;
						COND(0 == yytext[1], "String contains escaped null character.");

						if (EOF == yytext[1])	{
							if (ineof)
								yyterminate(); 
							ineof = 1;
							ERR("EOF in string constant");
						}
						string_buf_push(yytext[1]); curr_lineno += (yytext[1] == '\n'); 
						}
					

<string>[^\\\n\"]		{ 
							if (EOF == yytext[0]) 	{
								if (ineof)
									yyterminate(); 
								ineof = 1;
								ERR("EOF in string constant");
							}
							if (0 == yytext[0])
								failstr = 1;
							COND(0 == yytext[0], "String contains null character.");

							string_buf_push(yytext[0]); 
						}


.				{ ERR(yytext); }


%%
