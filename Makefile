CC      = gcc
CFLAGS  = -g
RM      = rm -f


all: main

main: main.c parser.y lexeur.l AST.c AST.h
	bison -d parser.y
	flex lexeur.l
	$(CC) $(CFLAGS) -o main main.c parser.tab.c lex.yy.c AST.c

clean:
	$(RM) parser.tab.c parser.tab.h lex.yy.c
