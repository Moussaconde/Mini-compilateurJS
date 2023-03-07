/* file main.c
* compilation: gcc -o compiler main.c parser.tab.c lexer.tab.c
* result: executable
*/
#include <stdio.h>
#include <stdlib.h>
int main(void) 
{
	if (!yyparse())
       	{ // call to the parsing (and lexing) function
		printf("\nParsing:: c'est bien une expression arithmétique\n"); // reached if parsing follow
	}
	exit(EXIT_SUCCESS);
}
