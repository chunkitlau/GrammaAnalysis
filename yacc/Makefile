expression:
	flex expression.lex
	bison -vdty expression.y
	gcc -o expression y.tab.c lex.yy.c

clean:
	rm -f expression y.tab.c y.tab.h lex.yy.c