#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvore.h"
#include "codigoIntermediario.h"
#include "tabelaNumero.h"
#include "y.tab.h"

/////////////////////// Manipulação da lista encadeada//////////////////////
int temp_ctr = 1;

//Inicializa a lista e retorna seu endereço
lista * inicializar_lista (){
	lista *temp = (lista *) malloc(sizeof(lista));
	//no_lista *cursor  = (no_lista *) malloc(sizeof(no_lista));
	//temp->primeiro = cursor;
	return temp;
}

// retorna o ultimo nó da lista, caso a lista seja vazia, então retorna NULL
no_lista * ultimo_no(lista *l){
	if (l->primeiro == NULL){
		return NULL; 
	}
	else{
		no_lista * temp = (no_lista *) malloc(sizeof(no_lista));
		temp = l->primeiro;
		while(temp->proximo != NULL){
			temp = temp->proximo;
		}
		return temp;
	}
}

//Insere nó na lista, não retorna nada
void inserir_no_lista(lista *l, instrucao *inst) {
	//Busca o ultimo nó, se o primeiro estiver vazio, retorna NULL
	no_lista *atual = ultimo_no(l);

	//aloca espaço para o nó 
	no_lista *proximo = (no_lista *) malloc(sizeof(no_lista));

	//se o nó atual for NULL é alocado com um novo nó e recebe as instruções
	//caso contrario o proximo nó da lista é atribuido, e o nó anterior recebe o endereço do próximo
	

	if(atual == NULL){
		l->primeiro = proximo;
		proximo->dado = inst;
		proximo->proximo = NULL;	
	}else{
		proximo->dado = inst;
		atual->proximo = proximo;
	}
}

//Aloca as instruções na lista encadeada e retorna o endereço dessa instrução
instrucao * criar_instrucao( int opcode, void *resultado, void *esq, void *dir){
	instrucao *temp = (instrucao *) malloc(sizeof(instrucao));
	
	temp->opcode = opcode;
	temp->resultado = resultado;
	temp->esq = esq;
	temp->dir = dir;
	return temp;
}


///////////////////////// Geração de código ////////////////////////////

void gerar_codigo(no_arvore * raiz) {
	if(raiz != NULL) {
		switch(raiz->tipo) {
			case EXPR: 
				gerar_codigo_expr(raiz);
				break;
			case ATTR:
				gerar_codigo_attr(raiz);
				break;
			case LOGIC:
			case LOOP:
			case COND:
			case STMT:
			case STMTS:
			case DECL:
			case BLOCO:
			case PROGRAM:
			

				break;
		}
	}
}
char * gerar_temp() {
	char buffer[256];
	sprintf(buffer, "t%d", temp_ctr++);
	return strdup(buffer);
}


char * gerar_codigo_expr(no_arvore *raiz) {
	char buffer[256];
	char *addr1, *addr2, *addr3;
	if(raiz != NULL) {
		simbolo *s;

		t_expr * dado = raiz->dado.expr;
		numero *num = dado->dir;
		switch (dado->op) {
			case INT:
				
				sprintf(buffer, "%d", num->val.dval);
				return strdup(buffer);	
			case FLOAT: 
				sprintf(buffer, "%f", num->val.fval);
				return strdup(buffer);
			case ID:
				s = (simbolo *) dado->dir;
				return s->lexema;

			case '+':
			case '-':
				
				addr1 = gerar_codigo_expr((no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr((no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				printf("%s = %s %c %s\n", addr3, addr1, dado->op, addr2);
				return addr3;

		}
	}else{ printf("é nulo\n");}
}

void gerar_codigo_attr(no_arvore *raiz) {
	t_attr * dado = raiz->dado.attr;	
	char * addr = gerar_codigo_expr(dado->expressao);
	simbolo *s = (simbolo *) dado->resultado;
	printf("%s = %s\n", s->lexema, addr);
}

void gerar_codigo_logic(no_arvore *raiz) {
	//t_attr * dado = raiz->dado.attr;	
	///char * addr = gerar_codigo_expr(dado->expressao);
	//simbolo *s = (simbolo *) dado->resultado;
	//printf("%s = %s\n", s->lexema, addr);
}



//Imprime toda a lista, de forma linear
void imprimir_lista(lista *l){
	printf("Inicio do imprimir Código\n");
	no_lista *cursor  = (no_lista *) malloc(sizeof(no_lista));
	cursor = l->primeiro;
	if(cursor == NULL)
		printf("Lista vazia");
	do{
		printf("%d\n", cursor->dado->opcode);
		cursor = cursor->proximo;
	//Estava dando erro aqui, cuidado para não instanciar um apontador de um null( proximo de um proximo)
	}while(cursor != NULL);
	printf("fim do imprimir código\n");
}

/*

no_lista * expr_lista(no_arvore *n){
	
	t_expr *expr = n->dado.expr;
	instrucao *inst = criar_instrucao(expr->op, ,expr->esq, expr->dir);
	
	no_lista *no = (no_lista *) malloc(sizeof(no_lista));
	no->dado = inst;
	
	return  no;
	
}

no_lista * attr_lista(no_arvore *n){
	
	t_attr *expr = n->dado.expr;
	instrucao *inst = criar_instrucao(SAVE, expr->resultado, exp->esq, exp->dir);
	
	no_lista *no = (no_lista *) malloc(sizeof(no_lista));
	no->dado = inst;
	
	return  no;
	
}

*/