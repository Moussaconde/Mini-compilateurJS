/* file lexeur.l
* compilation: flex lexeur.l
* result: lex.yy.c = lexical analyser in C
*/

%{
#include <stdio.h> // printf
#include "parser.tab.h" // token constants defined in parseur.y via #define

%}

%%


\.[0-9]+|[0-9]+\.?[0-9]*	{ printf("lex: création token NUMBER %s\n",yytext);
	 	  return NUMBER; }


"True" | "False" 	{ return BOOLEAN ;}

[[:space:]]*"=="[[:space:]]*		{ return EQUAL; }

[[:space:]]*"<="[[:space:]]*		{ return LESS_EQUAL;}

[[:space:]]*">="[[:space:]]*		{ return GR_EQUAL; }

[[:space:]]*"!="[[:space:]]*		{ return NOT_EQUAL; }

[[:space:]]*"!"[[:space:]]*		{ return NEGATION; }

[[:space:]]*">"[[:space:]]*		{ return GREATER; }

[[:space:]]*"<"[[:space:]]*		{ return LESSER; }


[0-9]*\.?[0-9]+e-?[0-9]+	{ return NUMBER; }

[a-zA-Z_][a-zA-Z0-9_]*		{ return IDENT; }

[[:space:]]*import[[:space:]]+			{ return IMPORT; }

[[:space:]]*if[[:space:]]*		{ return IF; }

[[:space:]]*else[[:space:]]*		{ return ELSE; }

[[:space:]]*while[[:space:]]*		{ return WHILE; }

[[:space:]]*function[[:space:]]*		{ return FUNCTION; }

[[:space:]]*return[[:space:]]*		{ return RETURN; }

\/\/.*				{ printf("Commentaire \n");
					return 0; }


"NaN"			{ return NUMBER;}

[[:space:]]*"&&"[[:space:]]*			{ return AND; }

[[:space:]]*"="[[:space:]]*			{ return ASSIGN; }


[ \t\r]	{ ; } // separator

\n	{ printf("lex: fin de lecture");
	  return 0; }

.	{ printf("lex: création token %s\n",yytext);
	  return yytext[0]; }


%%
int yywrap(void){ return 1; } // function called at the end of the file
