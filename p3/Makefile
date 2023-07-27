HEADERS = $(shell find . -name "*.h")
CFILES = codegen.c node.c

LYCFILES = y.tab.c lex.yy.c

OBJS = $(CFILES:.c=.o)
LYOBJS = $(LYCFILES:.c=.o)
CFLAGS = -g

-include $(patsubst, %.o, %.d, $(OBJS))

codegen:		$(OBJS) $(LYOBJS)
			gcc $(OBJS) $(LYOBJS) -o codegen -lfl

y.tab.c:	parser.y
			bison -v -y -d -g -t --verbose parser.y

lex.yy.c:	parser.l
			flex -l parser.l

clean:
	rm -f lex.yy.c y.tab.c y.tab.h y.dot y.output codegen $(OBJS) $(LYOBJS) *.s
