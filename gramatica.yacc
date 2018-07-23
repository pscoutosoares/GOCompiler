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
%token LT LE EQ NE GT GE 
%token PRINT SCAN NUMBER EXPR ATTR VAR IF ELSE FOR

%left '+' '-'
%left '*' '/'
%%


program:
	program bloco {}
	|
	; 	

bloco: 
	cond '{' 	{ }
	| loop '{'	{}
 	| decls stmts '}' 	{ }
	;

cond:
	IF logic bloco
	;
loop:
	FOR logic bloco
	; 

logic:
	expr LT expr 
	| expr LE expr
	| expr EQ expr 
	| expr NE expr
	| expr GT expr
	| expr GE expr
	;

decls: 
	decls decl		{ }
	|
	;
decl:
	VAR ID TYPE ';' 	{	}
	;

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
