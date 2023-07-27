CC=gcc
LEX=lex
GENERATED=lexer.c lex.yy.c

all: parser

parser: lex.yy.c parser.c
	$(CC) lex.yy.c parser.c -o parser

lex.yy.c: lexer.l
	$(LEX) lexer.l

clean:
	rm -f $(GENERATED) parser
