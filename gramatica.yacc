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
%token FOR  
%token IF ELSE
%token LT LE EQ NE GT GE 
%token PRINT SCAN 
%token EXPR ATTR VAR

%left '+' '-'
%left '*' '/'
%token NUMBER
%right UMINUS  
%%


program:
	program bloco {}
	|
	; 	

bloco: 
	'{' 	{}
 	decls stmts '}' 	{ }
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
	cond
	| loop
	| expr ';'		{	}
	| bloco			{ }
	| attr			{	}
	;

cond:
	IF logic bloco
	| IF logic bloco ELSE bloco   {}
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

attr: 
	ID '=' expr ';'		{ }
	;

expr:
	expr '+' expr		{ }
	| expr '-' expr		{ }
	| expr '*' expr		{ }
	| expr '/' expr		{ }
	| '(' expr ')'		{ }
	| NUMBER	{ }
	| ID { }
	; 

%%

void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}

int main(void) {
	//pilha = NULL;
	yyparse();
	return 0;
}
