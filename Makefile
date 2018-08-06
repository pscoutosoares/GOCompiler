all: teste
teste: y.tab.c lex.yy.c *.c *.h
		gcc -g -Wno-int-to-pointer-cast -o  teste *.c 
y.tab.c: gramatica.yacc
		yacc -d gramatica.yacc
lex.yy.c: lexico.lex
		lex lexico.lex
clean:
		rm y.tab.c y.tab.h lex.yy.c teste
test: teste teste.in
		./teste < teste.in 

