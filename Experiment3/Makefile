lex.yy.c: lex.l
	flex lex.l
parser: lex.yy.c parser.tab.c semantics.c
	gcc -o parser parser.tab.c semantics.c lex.yy.c -L /System/Volumes/Data/opt/homebrew/Cellar/flex/2.6.4_2/lib/ -lfl -I.
parser.tab.c : parser.y
	bison -d parser.y
run: parser
	./parser test.c 
.PHONY: run