/* file lexeur.l
* compilation: flex lexeur.l
* result: lex.yy.c = lexical analyser in C
*/

%{
#include <stdio.h> // printf
#include "AST.h"
#include "parser.tab.h" // token constants defined in parseur.y via #define

%}

%%



\.[0-9]+|[0-9]+\.?[0-9]*  { printf("lex::NUMBER %s\n", yytext);
			    yylval.number = atof(yytext);
	 	  	    return NUMBER; }

"True"|"False" 	{
			printf("lex::BOOLEAN %s\n", yytext);
			yylval.boolean =strdup(yytext);
			return BOOLEAN ;}

"+"		{ return ADDITION;}

"-"		{ return SUBSTRACTION;}

"*"		{ return MULTIPLICATION;}

"/"		{ return DIVISION; } 

"=="		{ return EQUAL; }

"<="		{ return LESS_EQUAL;}

">="		{ return GR_EQUAL; }

"!="		{ return NOT_EQUAL; }

"!"		{ return NEGATION; }

">"		{ return GREATER; }

"<"		{ return LESSER; }


[0-9]*\.?[0-9]+e-?[0-9]+	{ 
		yylval.number = atof(yytext);
		return NUMBER; }

[a-zA-Z_][a-zA-Z0-9_]*		{ return IDENT; }

[[:space:]]*import[[:space:]]			{ return IMPORT; }


\/\/.*				{ printf("Commentaire \n");
					return 0; }


"NaN"			{
				yylval.number = atoi(yytext);
				 return NUMBER;}

"&&"			{ return AND; }


[\t\r]	{ ; } // separator

\n	{ printf("lex: fin de lecture");
	  return 0; }

.	{ printf("lex: création token %s\n",yytext);
	  return yytext[0]; }


%%
int yywrap(void){ return 1; } // function called at the end of the file
