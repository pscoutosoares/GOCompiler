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
%token EXPR ATTR VAR STMT STMTS BLOCO PROGRAM LOGIC COND LOOP
%token ADD SUB
%token MUL DIV MOD
%token SAVE LOAD
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
			printf("%d\n",n->tipo);
			instrucao *inst = criar_instrucao(n->tipo, NULL, n->dado.program->program_e, n->dado.program->program_d);
			inserir_no_lista(list,inst);
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
	| loop			
		{
			no_arvore *n = criar_no_statement((void *) $1);
			$$ = (long int) n;
		}
	| expr ';'		
		{
			no_arvore *n = criar_no_statement((void *) $1);
			$$ = (long int) n;
		}
	| bloco			
		{
			no_arvore *n = criar_no_statement((void *) $1);
			$$ = (long int) n;
		}
	| attr			
		{
			no_arvore *n = criar_no_statement((void *) $1);
			$$ = (long int) n;
			//gerar_codigo((no_arvore *) $1);
		}
	| decl          
		{
			no_arvore *n = criar_no_statement((void *) $1);
			$$ = (long int) n;
		}
	;

cond:
	IF logic bloco
		{
			no_arvore *n = criar_no_cond((void *) $2, (void *) $3, NULL);
			$$ = (long int) n;
		}
	| IF logic bloco ELSE bloco   
		{
			no_arvore *n = criar_no_cond((void *) $2, (void *) $3, (void *) $5);
			$$ = (long int) n;
		}
	;

loop:
	FOR logic bloco
		{
			no_arvore *n = criar_no_loop((void *) $2, (void *) $3);
			$$ = (long int) n;
		}
	; 

logic:
	expr LT expr 
		{
			no_arvore *n = criar_no_logic(LT, (void *) $1, (void *) $3);
			$$ = (long int) n;

		}
	| expr LE expr
		{
			no_arvore *n = criar_no_logic(LE, (void *) $1, (void *) $3);
			$$ = (long int) n;

		} 
	| expr EQ expr
		{
			no_arvore *n = criar_no_logic(EQ, (void *) $1, (void *) $3);
			$$ = (long int) n;

		} 
	| expr NE expr
		{
			no_arvore *n = criar_no_logic(NE, (void *) $1, (void *) $3);
			$$ = (long int) n;

		}
	| expr GT expr
		{
			no_arvore *n = criar_no_logic(GT, (void *) $1, (void *) $3);
			$$ = (long int) n;

		}
	| expr GE expr
		{
			no_arvore *n = criar_no_logic(GE, (void *) $1, (void *) $3);
			$$ = (long int) n;

		}
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
			
			no_arvore * no_direita = (no_arvore *) $1;
			t_expr *dir = no_direita->dado.expr;

			no_arvore * no_esquerda = (no_arvore *) $3;
			t_expr *esq = no_esquerda->dado.expr;
			

			if(esq->tipo == FLOAT || dir->tipo == FLOAT)
				n->tipo = FLOAT;
			else
				n->tipo = INT;
				
		  	$$ = (long int) n;


		}
	| expr '-' expr		
		{
			no_arvore *n = criar_no_expressao('-', (void *) $1, (void *) $3); 
		  	
	  		no_arvore * no_direita = (no_arvore *) $1;
			t_expr *dir = no_direita->dado.expr;

			no_arvore * no_esquerda = (no_arvore *) $3;
			t_expr *esq = no_esquerda->dado.expr;
			

			if(esq->tipo == FLOAT || dir->tipo == FLOAT)
				n->tipo = FLOAT;
			else
				n->tipo = INT;
				
		  	$$ = (long int) n; 
		}
	| expr '*' expr		
		{
			no_arvore *n = criar_no_expressao('*', (void *) $1, (void *) $3); 
		  	
		  	no_arvore * no_direita = (no_arvore *) $1;
			t_expr *dir = no_direita->dado.expr;

			no_arvore * no_esquerda = (no_arvore *) $3;
			t_expr *esq = no_esquerda->dado.expr;
			

			if(esq->tipo == FLOAT || dir->tipo == FLOAT)
				n->tipo = FLOAT;
			else
				n->tipo = INT;
				
		  	$$ = (long int) n; 
		}
	| expr '/' expr		
		{
			no_arvore *n = criar_no_expressao('/', (void *) $1, (void *) $3); 
		  	
		  	no_arvore * no_direita = (no_arvore *) $1;
			t_expr *dir = no_direita->dado.expr;

			no_arvore * no_esquerda = (no_arvore *) $3;
			t_expr *esq = no_esquerda->dado.expr;
			

			if(esq->tipo == FLOAT || dir->tipo == FLOAT)
				n->tipo = FLOAT;
			else
				n->tipo = INT;
				
		  	$$ = (long int) n; 
		}
	| '(' expr ')'		
		{ 
			$$ = $2; 
		}
	| NUMBER 			
		{ 

			//capturar o tipo, na tabela de simbolos 
			numero *t_num = (numero *) $1;
			no_arvore *n = criar_no_expressao(t_num->tipo, (void *) $1, NULL); 
		  	
		  	$$ = (long int) n;  
		}
	| ID 
		{ 
			simbolo * s = localizar_simbolo(topo_pilha(pilha), (char *) $1);
		  	if(s == NULL)
				yyerror("Identificador não declarado");
		  	else  {
				no_arvore *n = criar_no_expressao(ID, s, NULL);
				//n->tipo = s->tipo;
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
