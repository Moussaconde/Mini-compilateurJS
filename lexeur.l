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

"=="		{ return EQUAL; }

"<="		{ return LESS_EQUAL;}

">="		{ return GR_EQUAL; }

"!="		{ return NOT_EQUAL; }

"!"		{ return NEGATION; }

">"		{ return GREATER; }

"<"		{ return LESSER; }


[0-9]*\.?[0-9]+e-?[0-9]+	{ return NUMBER; }

[a-zA-Z_][a-zA-Z0-9_]*		{ return IDENT; }

[[:space:]]*import[[:space:]]			{ return IMPORT; }


\/\/.*				{ printf("Commentaire \n");
					return 0; }


"NaN"			{ return NUMBER;}

"&&"			{ return AND; }

"="			{ return ASSIGN; }


[\t\r]	{ ; } // separator

\n	{ printf("lex: fin de lecture");
	  return 0; }

.	{ printf("lex: création token %s\n",yytext);
	  return yytext[0]; }


%%
int yywrap(void){ return 1; } // function called at the end of the file
