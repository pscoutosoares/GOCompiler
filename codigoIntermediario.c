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
instrucao * criar_instrucao(int opcode, char *resultado, char *esq, char *dir){
	instrucao *temp = (instrucao *) malloc(sizeof(instrucao));
	
	temp->opcode = opcode;
	temp->resultado = resultado;
	temp->esq = esq;
	temp->dir = dir;
	return temp;
}

//Imprime toda a lista, de forma linear
void imprimir_lista(lista *l){
	printf("Inicio do imprimir Código\n");
	no_lista *cursor  = (no_lista *) malloc(sizeof(no_lista));
	cursor = l->primeiro;
	if(cursor == NULL)
		printf("Lista vazia\n");
	else{
		do{
			char *c;
			c = mapear_tipo(cursor->dado->opcode);
			printf("%s %s %s %s\n", c, cursor->dado->resultado, cursor->dado->esq,  cursor->dado->dir);
			cursor = cursor->proximo;
			//Estava dando erro aqui, cuidado para não instanciar um apontador de um null( proximo de um proximo)
		}while(cursor != NULL);
	}
	printf("fim do imprimir código\n");
}


///////////////////////// Geração de código ////////////////////////////

void gerar_codigo(lista *l, no_arvore * raiz) {
	char *c;
	
	if(raiz != NULL) {
		c = mapear_tipo(raiz->tipo);
		printf("%s\n", c);
		switch(raiz->tipo) {
			case EXPR:
				gerar_codigo_expr(l, raiz);
				break;
			case ATTR:
				gerar_codigo_attr(l,raiz);
				break;
			case LOGIC:
				gerar_codigo_logic(l, raiz);
				break;
			case LOOP:
			
				break;
			case COND:
				gerar_codigo_cond(l, raiz);
				break;
			case STMT:
				gerar_codigo_stmt(l, raiz);
				break;
			case STMTS:
				gerar_codigo_stmts(l, raiz);
				break;
			case DECL:
			
				gerar_codigo_decl(l, raiz);
				break;
			case BLOCO:
	
				gerar_codigo_bloco(l, raiz);
				break;
			case PROGRAM:
				gerar_codigo_program(l, raiz);
				break;
		}
	}
}


void gerar_codigo_program(lista *l, no_arvore * no){
	if(no != NULL) {
		no_arvore *no_direita = no->dado.program->program_d;
		no_arvore *no_esquerda = no->dado.program->program_e;

		gerar_codigo(l,no_direita);
		gerar_codigo(l,no_esquerda);
	}
}


void gerar_codigo_bloco(lista *l, no_arvore * no_bloco){
	if(no_bloco != NULL) {

		no_arvore *no_stmts = no_bloco->dado.bloco->conteudo;
		gerar_codigo(l,no_stmts);
	}
}


void gerar_codigo_stmts(lista *l, no_arvore * no_stmts){
	if(no_stmts != NULL) {

		no_arvore *no_stmt_esquerda = no_stmts->dado.stmts->declaracao_e;
		no_arvore *no_stmt_direita = no_stmts->dado.stmts->declaracao_d;
		
		gerar_codigo(l,no_stmt_direita);
		gerar_codigo(l,no_stmt_esquerda);
	}
}
void gerar_codigo_stmt(lista *l ,no_arvore *no){
	if(no != NULL) {
		no_arvore *no_declaracao = no->dado.stmt->declaracao;
		//printf("tipo:%d\n", no_declaracao->tipo );
		gerar_codigo(l, no_declaracao);
	}
}

void gerar_codigo_decl(lista *l, no_arvore * no){
	if(no != NULL) {
		char *resultado, *direita, *esquerda;
		
		no_arvore *no_decl = no->dado.stmt->declaracao;
		simbolo *s = no_decl->dado.decl->id;
		direita = strdup(s->lexema);
		
		resultado = "LOAD";
		instrucao *i = criar_instrucao(no->tipo,resultado,direita,NULL);

		inserir_no_lista(l,i);
	}
}

void gerar_codigo_cond(lista *l, no_arvore * no){

	if(no != NULL) {

		no_arvore *no_logica = no->dado.cond->cond_logica;
		no_arvore *no_inf = no->dado.cond->cond_if;
		no_arvore *no_else = no->dado.cond->cond_else;
		
		gerar_codigo(l,no_logica);
		gerar_codigo_bloco(l,no_inf);
		gerar_codigo_bloco(l,no_else);



		//char *resultado, *direita, *esquerda;
		//no_arvore *no_decl = no->dado.stmt->declaracao;
		//simbolo *s = no_decl->dado.decl->id;
		//direita = strdup(s->lexema);
		//instrucao *i = criar_instrucao(no->tipo,resultado,direita,"LABEL_IF");
		//inserir_no_lista(l,i);
	}
}
void gerar_codigo_logic(lista *l ,no_arvore *no) {
	
	if(no != NULL) {

		int op = no->dado.logic->op;
		no_arvore *no_logic_esquerda = no->dado.logic->esq;
		no_arvore *no_logic_direita = no->dado.logic->dir;
		
		gerar_codigo(l,no_logic_esquerda);
		gerar_codigo(l,no_logic_direita);
	}
}


char * gerar_temp() {
	char buffer[256];
	sprintf(buffer, "t%d", temp_ctr++);
	return strdup(buffer);
}


char * gerar_codigo_expr(lista *l, no_arvore *raiz) {
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
				
				addr1 = gerar_codigo_expr(l,(no_arvore *) dado->dir);
				addr2 = gerar_codigo_expr(l,(no_arvore *) dado->esq);
				addr3 = gerar_temp(); 				
				printf("%s = %s %c %s\n", addr3, addr1, dado->op, addr2);
				return addr3;

		}
	}else{ printf("é nulo\n");}
}

void gerar_codigo_attr(lista *l, no_arvore *raiz) {
	t_attr * dado = raiz->dado.attr;	
	char * addr = gerar_codigo_expr(l, dado->expressao);
	simbolo *s = (simbolo *) dado->resultado;
	printf("%s = %s\n", s->lexema, addr);
}





char * mapear_tipo(int tipo){
	char *cod;
	
	switch(tipo) {
		case EXPR:
			cod = "EXPR";
			break;
		case ATTR:
			cod ="ATTR";
			break;
		case LOGIC:
			cod ="LOGIC";
			break;
		case LOOP:
			cod ="LOOP";
			break;
		case COND:
			cod ="COND";
			break;
		case STMT:
			cod ="STMT";
			break;
		case STMTS:
			cod ="STMTS";
			break;
		case DECL:
			cod ="DECL";
			break;
		case BLOCO:
			cod ="BLOCO";
			break;
		case PROGRAM:
			cod ="PROGRAM";
			break;
		default:
			cod = " ";
			//sprintf(cod,"Cod não encontrado %d",tipo);
	}	
	return cod;
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