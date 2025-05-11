CC = g++
FLEX = flex
BISON = bison

CFLAGS = -g -Iinc

FOLDER_MISC = misc
FOLDER_SRC = src
FOLDER_INC = inc

all: assembler

assembler: $(FOLDER_MISC)/lexer.l $(FOLDER_MISC)/parser.y $(FOLDER_SRC)/main.cpp $(FOLDER_SRC)/LineProcessor.cpp $(FOLDER_INC)/LineProcessor.h $(FOLDER_SRC)/Line.cpp $(FOLDER_INC)/Line.h
	$(BISON) -d -o $(FOLDER_MISC)/parser.tab.c $(FOLDER_MISC)/parser.y
	$(FLEX) -o $(FOLDER_MISC)/lex.yy.c $(FOLDER_MISC)/lexer.l
	$(CC) $(CFLAGS) -o assembler $(FOLDER_MISC)/lex.yy.c $(FOLDER_MISC)/parser.tab.c $(FOLDER_SRC)/LineProcessor.cpp $(FOLDER_SRC)/Line.cpp $(FOLDER_SRC)/main.cpp -lfl

clean:
	rm -f assembler $(FOLDER_MISC)/lex.yy.c $(FOLDER_MISC)/parser.tab.c $(FOLDER_MISC)/parser.tab.h