lex.yy.c: lex.l
	flex lex.l
lexScan: lex.yy.c
	gcc -o lexScan lex.yy.c -L /System/Volumes/Data/opt/homebrew/Cellar/flex/2.6.4_2/lib/ -lfl
run: lexScan
	./lexScan test.c
.PHONY: run