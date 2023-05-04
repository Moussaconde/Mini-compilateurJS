/* file parseur.y
* compilation: bison -d parseur.y
* result: parseur.tab.c = C code for syntaxic analyser
* result: parseur.tab.h = def. of lexical units aka lexems
*/
%{ // the code between %{ and %} is copied at the start of the generated .c
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include "AST.h"
	int yylex(void); // -Wall : avoid implicit call
	int yyerror(AST_prog*, const char*); // on fonctions defined by the generator
%}


%parse-param {AST_prog *rez}
%union {
	float number;
	char *boolean;
	char *id;
	AST_expr expr;
	AST_comm comm;
	AST_prog prog;
}


%start programme
%left AND
%left NOT_EQUAL EQUAL
%left LESSER LESS_EQUAL GREATER GR_EQUAL
%left ADDITION SUBSTRACTION
%left MULTIPLICATION DIVISION
%nonassoc NEG
%left UMOINS



%type   <expr>		expression
%type   <comm>		commande
%type	<prog>		programme


%token			AND
%token	<id>		IDENT
%token			IMPORT
%token			ADDITION
%token			SUBSTRACTION
%token			MULTIPLICATION
%token			DIVISION
%token	<number>	NUMBER
%token	<boolean>	BOOLEAN
%token 			EQUAL
%token 			LESS_EQUAL
%token 			GR_EQUAL
%token 			LESSER
%token 			GREATER
%token 			NOT_EQUAL
%token			NEGATION


%% // denotes the begining of the grammar with bison-specific syntax

programme:
	   %empty
		{ *rez = new_program(NULL);}
	 | commande programme
		{
			AST_command_list command_list = malloc(sizeof(struct _command_list));
     			command_list->command = $1;
      			command_list->next = (*rez)->command_list;
     			(*rez)->command_list = command_list;
     			*rez = new_program((*rez)->command_list); 
		}
	 ;

commande: expression ';'
		{ $$ = new_command($1); }
	| IMPORT IDENT ';'
		{printf("%s", $2); $$ = new_command(new_import_expr($2)); }

expression: // an expression is
	  expression ADDITION expression // either a sum of an expression and a term
		{
			char *r = (char *) malloc(sizeof(ADDITION)+1);
			strcpy(r, "+");
			$$ = new_binary_expr(r,$1,$3);
		}
	| expression SUBSTRACTION expression // or an expression minus a term
		{ 
			char *r = (char *) malloc(sizeof(SUBSTRACTION)+1);
			strcpy(r, "-");
			$$ = new_binary_expr(r,$1,$3); 
		}
	| expression MULTIPLICATION expression
		{
			char *r = (char *) malloc(sizeof(MULTIPLICATION)+1);
			strcpy(r, "*");
			$$ = new_binary_expr(r,$1,$3);
		}
	| expression DIVISION expression
		{ 
			char *r = (char *) malloc(sizeof(DIVISION)+1);
			strcpy(r, "/");
			$$ = new_binary_expr(r,$1,$3); 
		}
	| '(' expression ')'
		{
			$$ = $2; 
		}
	| SUBSTRACTION  expression %prec UMOINS
		{
			char *r = (char *) malloc(sizeof(UMOINS)+1);
			strcpy(r, "M");
			$$ = new_unary_expr(r,$2); 
		}
	| NUMBER
		{
			$$ = new_number_expr($1); 
		}
	| expression LESSER expression
		{
			char *r = (char *) malloc(sizeof(LESSER)+1);
			strcpy(r, "<");
			$$ = new_binary_expr(r, $1, $3);
		}
	| expression GREATER expression
		{
			char *r = (char *) malloc(sizeof(GREATER)+1);
			strcpy(r, ">");
			$$ = new_binary_expr(r, $1, $3);
		}
	| expression EQUAL expression
		{
			char *r = (char *) malloc(sizeof(EQUAL)+1);
			strcpy(r, "==");
			$$ = new_binary_expr(r, $1, $3);
		}
	| expression LESS_EQUAL expression 
		{
			char *r = (char *) malloc(sizeof(LESS_EQUAL)+1);
			strcpy(r, "<=");
			$$ = new_binary_expr(r, $1, $3);
		}
	| expression GR_EQUAL expression
		{
			char *r = (char *) malloc(sizeof(GR_EQUAL)+1);
			strcpy(r, ">=");
			$$ = new_binary_expr(r, $1, $3);
		}
	| expression NOT_EQUAL expression 
		{ 
			char *r = (char *) malloc(sizeof(NOT_EQUAL)+1);
			strcpy(r, "!=");
			$$ = new_binary_expr(r, $1, $3);
		}
	| expression AND expression 
		{ 
			char *r = (char *) malloc(sizeof(NOT_EQUAL)+1);
			strcpy(r, "&&");
			$$ = new_binary_expr(r, $1, $3);
		}
	
	| NEGATION expression %prec NEG
		{
			char *r = (char *) malloc(sizeof(NEGATION)+1);
			strcpy(r, "!");
			$$ = new_unary_expr(r, $2);
		}
	| BOOLEAN 
		{
			char *b = (char *) malloc(6*sizeof(char));
			strcpy(b, $1);
			$$ = new_boolean_expr($1); }


%% // denotes the end of the grammar
// everything after %% is copied at the end of the generated .c
int yyerror(AST_prog* rez, const char *msg)
{ // called by the parser if the parsing fails
	printf("Parsing:: syntax error\n");
	return 1; // to distinguish with the 0 retured by the success
}
