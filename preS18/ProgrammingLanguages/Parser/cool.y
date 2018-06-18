/*
 *  cool.y
 *
 *	Names: Kodi Neumiller & Nathan Lewis
 * 	Class: Concepts of Programming Languages
 *	Date:  12/13/16
 *
 *	Definition: Parser definition for the COOL scanner in
 *		COOL language.
 *
 */
%{
/*lk
   See copyright.h for copyright notice, limitation of liability,
   and disclaimer of warranty provisions.
*/
#include "copyright.h"
#include "cool-io.h" //includes iostream
#include "cool-tree.h"
#include "stringtab.h"
#include "utilities.h"

/* Locations */
#define YYLTYPE int              /* the type of locations */
#define cool_yylloc curr_lineno  /* use the curr_lineno from the lexer
                                    for the location of tokens */
extern int node_lineno;          /* set before constructing a tree node
                                    to whatever you want the line number
                                    for the tree node to be */

/* The default action for locations.  Use the location of the first
   terminal/non-terminal and set the node_lineno to that value. */
#define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current = Rhs[1];                             \
  node_lineno = Current;

#define SET_NODELOC(Current)  \
  node_lineno = Current;

extern char *curr_filename;

void yyerror(char *s);        /*  defined below; called for each parse error */
extern int yylex();           /*  the entry point to the lexer  */
Program ast_root;	            /* the result of the parse  */
Classes parse_results;        /* for use in semantic analysis */
int omerrs = 0;               /* number of erros in lexing and parsing */

%}

/* A union of all the types that can be the result of parsing actions. */
%union {
  Boolean boolean;
  Symbol symbol;
  Program program;
  Class_ class_;
  Classes classes;
  Feature feature;
  Features features;
  Formal formal;
  Formals formals;
  Case case_;
  Cases cases;
  Expression expression;
  Expressions expressions;
  char *error_msg;
}

/* Declare types for the grammar's non-terminals. */
%type <program> program

%type <class_> class
%type <classes> class_list


%type <feature> feature
%type <features> feature_list

%type <formal> formal
%type <formals> formal_list

%type <case_> case
%type <cases> case_list

%type <expression> expression
/* expression_set is separated by ; */
%type <expressions> expression_set
/* expression_list is separated by , */
%type <expressions> expression_list

/* 
   Declare the terminals; a few have types for associated lexemes.
   The token ERROR is never used in the parser; thus, it is a parse
   error when the lexer returns it.

   The integer following token declaration is the numeric constant used
   to represent that token internally.  Typically, Bison generates these
   on its own, but we give explicit numbers to prevent version parity
   problems (bison 1.25 and earlier start at 258, later versions -- at
   257)

 */
%token CLASS 258 ELSE 259 FI 260 IF 261 IN 262 
%token INHERITS 263 LET 264 LOOP 265 POOL 266 THEN 267 WHILE 268
%token CASE 269 ESAC 270 OF 271 DARROW 272 NEW 273 ISVOID 274
%token <symbol>  STR_CONST 275 INT_CONST 276 
%token <boolean> BOOL_CONST 277
%token <symbol>  TYPEID 278 OBJECTID 279 
%token ASSIGN 280 NOT 281 LE 282 ERROR 283

/* Precedence declarations. */

%right ASSIGN
%nonassoc NOT
%nonassoc LE '<' '='
%left '+' '-'
%left '*' '/'
%nonassoc ISVOID
%nonassoc '~'
%nonassoc '@'
%nonassoc '.'

%%
/* 
   Save the root of the abstract syntax tree in a global variable.
*/
program	: class_list	{ /* make sure bison computes location information */
                          @$ = @1;
                          ast_root = program($1); }
        | error         { ast_root = program(nil_Classes()); }
        ;

class_list : class
				
/* single class */
		{ $$ = single_Classes($1);
          parse_results = $$; }
	| error ';' 
/* error in the first class */
		{ $$ = nil_Classes(); }
	| class_list class	
/* several classes */
		{ $$ = append_Classes($1,single_Classes($2)); 
          parse_results = $$; }
	| class_list error ';'  
/* error message */
		{  $$ = $1; }
	;

/* If there is no parent specified,then the class will inherit from the Object class. */
	class : CLASS TYPEID '{' feature_list '}' ';'{ 
		@$ = @1;
		SET_NODELOC(@1);
		$$ = class_($2,idtable.add_string("Object"),$4,
			stringtable.add_string(curr_filename)); }
	| CLASS TYPEID INHERITS TYPEID '{' feature_list '}' ';' {
		@$ = @1;
		SET_NODELOC(@1);	
		$$ = class_($2,$4,$6,stringtable.add_string(curr_filename)); 
	}
	;

/* Feature List may be empty, but no empty features in list. */
	feature_list : 
	/*if the list is empty*/
		{ $$ = nil_Features(); }
	| feature_list feature { 
	/* case for multiple features */
		$$ = append_Features($1, single_Features($2));
	};

/* Feature can be either a method or attribute */
	feature : OBJECTID '(' formal_list ')' ':' TYPEID '{' expression '}' ';' {
	/*object id set to multiple expressions */
		@$ = @1;
		SET_NODELOC(@1);
		$$ = method($1,$3,$6,$8); }
	|	OBJECTID ':' TYPEID ASSIGN expression ';'{
	/*object id set to just one expression */
		@$ = @1;
		SET_NODELOC(@1);
		$$ = attr($1, $3, $5); }
	| OBJECTID ':' TYPEID ';' { 
	/*there is no initial value present*/
		@$ = @1;
		SET_NODELOC(@1);
		$$ = attr($1, $3, no_expr());
	};
	
/*--- A formal list can be empty ----*/
	formal_list: {	
/*empty */ 
		$$ = nil_Formals();	}
	| formal { 
/* single formal */
	$$ = single_Formals($1);	}
	| formal_list ',' formal { 
/*multiple formals */
		$$ = append_Formals($1, single_Formals($3)); 
	};
	
	/*---- Formal -----*/
	formal : OBJECTID ':' TYPEID {
		@$ = @1;
		SET_NODELOC(@1);
		$$ = formal ($1,$3);
		};
		
/*---- Expression List, separated by a ',' ----*/
	expression_list: { 
/*empty list*/
	$$ = nil_Expressions(); }
	| expression {
		$$ = single_Expressions($1); }
	| expression_list ',' expression {
		$$ = append_Expressions($1, single_Expressions($3));
	};
	
/*---- Expression set, separated by a ';' ----*/
	expression_set: expression ';' { 
/* single expression*/
		$$ = single_Expressions($1);	}
	| expression_set expression ';' {
/* multiple expressions*/
		$$ = append_Expressions($1, single_Expressions($2));
	};
	
/*---- case and case lists that are used for expression ----*/
	case: OBJECTID ':' TYPEID DARROW expression {
		@$ = @1;
		SET_NODELOC(@1);
		$$ = branch($1,$3,$5);
	};
	
	case_list: case ';' {
	/* single case */ 
		$$ = single_Cases($1); }
	| case_list case { 
	/* multiple cases */
		$$ = append_Cases($1, single_Cases($2));
	};
	
/*---- Expressions -----*/
	expression: OBJECTID ASSIGN expression { 
/* ASSIGN an OBJECTID to an expression*/
		@$ = @3;
		SET_NODELOC(@3);
		$$ = assign($1,$3); }
	| '{' expression_set '}' {
/* A set of expressions */
		@$ = @2;
		SET_NODELOC(@2);
		$$ = block($2);	}
	| expression '@' TYPEID '.' OBJECTID '(' expression_list ')' {
/* static_dispatch*/
		@$ = @1;
		SET_NODELOC(@1);
		$$ = static_dispatch($1, $3, $5, $7); 	}
	| expression '.' OBJECTID '(' expression_list ')' {
/*normal dispatch*/
		@$ = @1;
		SET_NODELOC(@1);
		$$ = dispatch($1, $3, $5);	}
	| OBJECTID '(' expression_list ')' {
/* shorthand self normal dispatch */
		@$ = @1;
		SET_NODELOC(@3);
		$$ = dispatch(object(idtable.add_string("self")), $1, $3); }
		
		
	| IF expression THEN expression ELSE expression FI {
/* else is not optional!!!!!!!!!!!!!*/
		@$ = @2;
		SET_NODELOC(@2);
		$$ = cond($2, $4, $6); }
		
		
	| WHILE expression LOOP expression POOL {
/* While Loop */
		@$ = @1;
		SET_NODELOC(@1);
		$$ = loop($2, $4); }

		
	/*Let, but w/o multiple id:type.
	* use no_expr for empty initial value
	* use "let in"again after "let in" to create multiple bindings
	*/
	| LET OBJECTID ':' TYPEID IN expression {
/* Let without an initial value*/ 
		@$ = @2;
		SET_NODELOC(@2);
		$$ = let($2, $4, no_expr(), $6); }
	| LET OBJECTID ':' TYPEID ASSIGN expression IN expression {
/* Let with an initial value */	
		@$ = @2;
		SET_NODELOC(@2);
		$$ = let($2, $4, $6, $8);	}
		
	| CASE expression OF case_list ESAC {
/* Case */
		@$ = @2;
		SET_NODELOC(@2);
		$$ = typcase($2, $4); }
		
	| NEW TYPEID {
/* new typeID */
		@$ = @2;
		SET_NODELOC(@2);
		$$ = new_($2); }
		
	| ISVOID expression {
/* regular isVoid expression */ 
		@$ = @2;
		SET_NODELOC(@2);
		$$ = isvoid($2); }
		
	| '~' expression {
/* neglect the given expression */
		@$ = @2;
		SET_NODELOC(@2);
		$$ = neg($2); }
	| expression '<' expression {
/* check if an expression is less than another expression */
		@$ = @1;
		SET_NODELOC(@1);
		$$ = lt($1, $3); }
	| expression '=' expression {
/* checks if two expressions are equal */
		@$ = @1;
		SET_NODELOC(@1);
		$$ = eq($1, $3); }
	| expression '+' expression {
/* add two expressions together*/
		@$ = @1;
		SET_NODELOC(@1);
		$$ = plus($1, $3); }
	| expression '-' expression {
/* subtract one expression from another */
		@$ = @1;
		SET_NODELOC(@1);
		$$ = sub($1, $3); }
	| expression '*' expression {
/* get the product of two expression */
		@$ = @1;
		SET_NODELOC(@1);
		$$ = mul($1, $3); }
	| expression '/' expression {
/* get the quotient of two expressions */
		@$ = @1;
		SET_NODELOC(@1);
		$$ = divide($1, $3); }
	| NOT expression {
/* change the expression */
		@$ = @2;
		SET_NODELOC(@2);
		$$ = comp($2); }
	| '(' expression ')' {
/* do this expression first */
		@$ = @2;
		SET_NODELOC(@2);
		$$ = $2; }
	| expression LE expression {
		@$ = @1;
		SET_NODELOC(@1);
		$$ = leq($1, $3); }
	
/* single, simpler types */
	| OBJECTID {
/* the name of the object id */
		@$ = @1;
		SET_NODELOC(@1);
		$$ = object($1); }
	| INT_CONST {
/* numbers 0-9 */
		@$ = @1;
		SET_NODELOC(@1);
		$$ = int_const($1); }
	| STR_CONST {
/* the list of characters */
		@$ = @1;
		SET_NODELOC(@1);
		$$ = string_const($1); }
	| BOOL_CONST {
/* check for a true/false */
		@$ = @1;
		SET_NODELOC(@1);
		$$ = bool_const($1); }
	;
		
	
/* end of grammar */
%%

/* This function is called automatically when Bison detects a parse error. */
void yyerror(char *s)
{
  extern int curr_lineno;

  cerr << "\"" << curr_filename << "\", line " << curr_lineno << ": " \
    << s << " at or near ";
  print_cool_token(yychar);
  cerr << endl;
  omerrs++;
  if(omerrs>50) { cerr << "More than 50 errors" << endl; exit(1);}
}