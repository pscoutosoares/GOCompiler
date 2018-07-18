%{
#include <stdio.h>

int yylex(void);
void yyerror(char *);

%}

%union {
	int ival;	
	double dval;
}

%token <ival> INT 
%token <dval> FLOAT
%token <ival> ID
%token <ival> TYPE

%token PRINT SCAN NUMBER EXPR ATTR VAR

%left '+' '-'
%left '*' '/'
%%


program:
	program bloco { }
	|
	; 	

bloco: 
	cmd '{' 	{ }
 	| decls stmts '}' 	{ }
	|
	;

cmd:
	FUNC ID '(' method ')'
	;

params:
	params 
	cond
	|
	;
	
decls: 
	decls decl		{ }
	|
	;
decl:
	VAR ID TYPE ';' 	{	}
	;

//tentar implementar depois, declaração de multivalores em uma linha
/* 	
decl:
	VAR ids TYPE ';' 	{	}
	;

ids:
	ID ',' {}
	;
*/

stmts: 
	stmts stmt
	| 	
	;

stmt:
	expr ';'		{	}
	| bloco
	| attr			{	}
	;

attr: 
	ID '=' expr ';'		{ }
	;

expr:
 	NUMBER	{ }
	| ID { }
	| expr '+' expr		{ }
	| expr '-' expr		{ }
	| expr '*' expr		{ }
	| expr '/' expr		{ }
	| '(' expr ')'		{ }
	; 

%%

void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}

int main(void) {
	pilha = NULL;
	yyparse();
	return 0;
}
