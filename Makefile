#------------------------------------------------------------------------------
CPP=g++ 
SOURCE=lex.yy.c parser.tab.c ast.cc solver.cc 
MYPROGRAM=delta
MYLIBRARY=$(CURDIR)
LDFLAGS=-Wl,-rpath=$(CURDIR)
FLEX=flex
ALLHEADERS=headers.h
BISON=bison
#-----------------------------------------------------------------------------

all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE) $(ALLHEADERS)
	$(CPP) -std=gnu++11 -include $(ALLHEADERS) -L $(MYLIBRARY) $(LDFLAGS) $(SOURCE) -o $(MYPROGRAM) -lfl -ly

lex.yy.c: scanner.l parser.tab.h
	$(FLEX) -l --yylineno scanner.l
parser.tab.c parser.tab.h parser.output: parser.y
	$(BISON) -dv  parser.y

clean:
	rm -f $(MYPROGRAM)