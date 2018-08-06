%{
/*Em alguns computadores existe uma serie de segmentation erros com o cast de long int e ponteiro, então é necessario modificar o tipo defaut do yystype para long int  e se faz com as funções a baixo (ps: é necessario importar antes de qualquer outro include e importar tanto no yacc quanto no lexico) */
#ifndef YYSTYPE
# define YYSTYPE long int
#endif

#include <stdio.h>
#include "tabelaNumero.h"
#include "arvore.h"
#include "codigoIntermediario.h"

int yylex(void);
void yyerror(char *);

pilha_contexto *pilha;
lista *list;

%}


%token INT FLOAT ID TYPE 
%token FOR  
%token IF ELSE
%token LT LE EQ NE GT GE 
%token AND OR NOT
%token PRINT SCAN 
%token EXPR ATTR VAR STMT STMTS BLOCO PROGRAM
%token ADD SUB
%token MUL DIV MOD
%left '+' '-'
%left '*' '/'
%token NUMBER
%right UMINUS  
%%


program:
	program bloco 
		{
			no_arvore *n = criar_no_program((void *) $1, (void *) $2);

			$$ = (long int) n;

			lista *list = inicializar_lista();
			//printf("%d\n",n->tipo);
			instrucao *inst = criar_instrucao(n->tipo, NULL, n->dado.program->program_e, n->dado.program->program_d);
			inserir_no_lista(list,inst);
			imprimir_lista(list);
		}
	|
	; 	

bloco: 
	'{'
	 	{ 
			tabela *contexto = criar_contexto(topo_pilha(pilha));
		  	pilha = empilhar_contexto(pilha, contexto);
		} 
stmts '}' 
		{ 
			imprimir_contexto(topo_pilha(pilha));
		  	desempilhar_contexto(&pilha);

		  	//Não utilizei o cast para void aqui, pois presumo que o
		  	//$1 retorna o endereço que também é do tipo stmts
		  	//se algo der errado, provavel que foi isso
		  	no_arvore *n = criar_no_bloco((void *) $2);
			$$ = (long int) n;

		}
	;
decl:
	VAR ID TYPE ';' 	
		{ 
			simbolo * s = localizar_simbolo(topo_pilha(pilha), (char *) $2);
			if(s == NULL){
				//Cria um nó contendo o simbolo
				//Lembrar de dar o cast para char, pois apenas é passado o endereço no lex
				simbolo *s = criar_simbolo((char *) $2, $3);

				//insere o nó do simbolo na tabela do contexto atual,
				//apontado pela pilha
				inserir_simbolo(topo_pilha(pilha), s);
			}
			else  {
				yyerror("Identificador já declarado");
			}
		}
	;

stmts: 
	stmts stmt 
		{
			no_arvore *n = criar_no_statements((void *) $1, (void *) $2);
			$$ = (long int) n;
		}
	| 	
	;

stmt:
	cond
	| loop			{}
	| expr ';'		{}
	| bloco			{}
	| attr			
		{
			no_arvore *n = criar_no_statement((void *) $1);
			$$ = (long int) n;
		}
	| decl          {}
	;

cond:
	IF logic bloco
	| IF logic bloco ELSE bloco   {}
	;

loop:
	FOR logic bloco
	; 

logic:
	expr LT expr {}
	| expr LE expr 
	| expr EQ expr 
	| expr NE expr
	| expr GT expr
	| expr GE expr
	;

attr: 
	ID '=' expr ';'		
		{
			simbolo * s = localizar_simbolo(topo_pilha(pilha), (char *) $1);
			if(s == NULL)
				yyerror("Identificador não declarado");
			else  {
				no_arvore *n = criar_no_atribuicao(s, (void *) $3);
				$$ = (long int) n;
			}
		}
	;

expr:
	expr '+' expr		
		{
			no_arvore *n = criar_no_expressao('+', (void *) $1, (void *) $3); 
		  	$$ = (long int) n; 
		}
	| expr '-' expr		
		{
			no_arvore *n = criar_no_expressao('-', (void *) $1, (void *) $3); 
		  	$$ = (long int) n; 
		}
	| expr '*' expr		
		{
			no_arvore *n = criar_no_expressao('*', (void *) $1, (void *) $3); 
		  	$$ = (long int) n; 
		}
	| expr '/' expr		
		{
			no_arvore *n = criar_no_expressao('/', (void *) $1, (void *) $3); 
		  	$$ = (long int) n; 
		}
	| '(' expr ')'		
		{ 
			$$ = $2; 
		}
	| NUMBER 			
		{ 
			no_arvore *n = criar_no_expressao(NUMBER, (void *) $1, NULL); 
		  	$$ = (long int) n;  
		}
	| ID 
		{ 
			simbolo * s = localizar_simbolo(topo_pilha(pilha), (char *) $1);
		  	if(s == NULL)
				yyerror("Identificador não declarado");
		  	else  {
				no_arvore *n = criar_no_expressao(ID, s, NULL);
				$$ = (long int) n;
			}
	 	}
	; 

%%

void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}

int main(void) {
	pilha = NULL;
	list = NULL;
	yyparse();
	

	return 0;
}
