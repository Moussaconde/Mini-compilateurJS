/* file main.c
* compilation: gcc -o compiler main.c parser.tab.c lexer.tab.c
* result: executable
*/
#include <stdio.h>
#include <stdlib.h>
#include "AST.h"
int main(void) 
{

	AST_prog rez;
	if (!yyparse(&rez))
       	{ // call to the parsing (and lexing) function
	  	print_prog(rez);
		printf("\nParsing:: c'est bien une expression arithmétique\n"); // reached if parsing follow
	}
	exit(EXIT_SUCCESS);
}
