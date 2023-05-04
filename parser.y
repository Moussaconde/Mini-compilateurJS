/* file parseur.y
* compilation: bison -d parseur.y
* result: parseur.tab.c = C code for syntaxic analyser
* result: parseur.tab.h = def. of lexical units aka lexems
*/
%{ // the code between %{ and %} is copied at the start of the generated .c
	#include <stdio.h>
	int yylex(void); // -Wall : avoid implicit call
	int yyerror(const char*); // on fonctions defined by the generator
%}


%start programme
%right ASSIGN
%left AND
%left NOT_EQUAL EQUAL
%left LESSER LESS_EQUAL GREATER GR_EQUAL
%left '+' '-'
%left '*' '/'
%nonassoc NEGATION
%nonassoc UMOINS

%token		ASSIGN
%token		AND
%token		IDENT
%token		IMPORT
%token		NUMBER
%token		BOOLEAN
%token 		EQUAL
%token 		LESS_EQUAL
%token 		GR_EQUAL
%token 		LESSER
%token 		GREATER
%token 		NOT_EQUAL
%token		NEGATION

%% // denotes the begining of the grammar with bison-specific syntax

programme: %empty
	 | commande programme
	 ;

commande: expression ';'
	 | IMPORT IDENT ';'
	 ;

expression: // an expression is
	  expression '+' expression {
		printf("Addition\n");}
	| expression '-' expression {
		printf("Soustraction\n");}
	| expression '*' expression {
		printf("Multiplication\n");}
	| expression '/' expression {
		printf("Division\n");}
	| '(' expression ')' {
		printf("Entre parentheses\n");}
	| '-' expression %prec UMOINS {
		printf("- expression \n");}
	| expression LESSER expression {
		printf("INFerieur \n");}
	| expression GREATER expression {
		printf("SUPerieur\n");}
	| expression EQUAL expression {
		printf("EGAl\n");}
	| expression LESS_EQUAL expression {
		printf("INF ou egal\n"); }
	| expression GR_EQUAL expression {
		printf("SUP ou egal\n"); }
	| expression NOT_EQUAL expression {
		printf("EGAL OU PAS \n");}
	| NEGATION expression %prec NEGATION {
		printf("Negation expresssion\n");}
	| expression AND expression {
		printf("ET &&\n");}
	| NUMBER {
		printf("nombre\n");}
	| BOOLEAN {
		printf("booleen\n");}
	| IDENT ASSIGN expression {
		printf("variable\n");}
	;

%% // denotes the end of the grammar
// everything after %% is copied at the end of the generated .c
int yyerror(const char *msg)
{ // called by the parser if the parsing fails
	printf("Parsing:: syntax error\n");
	return 1; // to distinguish with the 0 retured by the success
}
