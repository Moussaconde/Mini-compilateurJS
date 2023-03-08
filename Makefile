CC      = gcc
CFLAGS  = -g
RM      = rm -f


all: main

main: main.c parser.y lexeur.l
	bison -d parser.y
	flex lexeur.l
	$(CC) -o main main.c parser.tab.c lex.yy.c

clean:
	$(RM) parseur.tab.c lex.yy.c
