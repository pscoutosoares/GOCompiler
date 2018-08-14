#ifndef CODIGO_INTERMEDIARIO_H
#define CODIGO_INTERMEDIARIO_H

#include "arvore.h"
#include <string.h>

typedef struct instrucao{
	//Opcode recebe o tipo de no_arovre
	int opcode;
	// as variaveis void recebem apontadores das suas respectivas estruturas
	char *resultado, *esq, *dir;
}instrucao;

typedef struct no_lista {
	instrucao *dado;
	struct no_lista *proximo;
} no_lista;

typedef struct lista {
	no_lista *primeiro;
} lista;


void inserir_no_lista(lista *l, instrucao *inst);
instrucao * criar_instrucao( int opcode, char *resultado, char *esq, char *dir);
no_lista * ultimo_no(lista *l);
lista * inicializar_lista();
void imprimir_lista(lista *l);


void gerar_codigo(lista *l, no_arvore * raiz);
void gerar_codigo_program(lista *l, no_arvore *raiz);
void gerar_codigo_bloco(lista *l, no_arvore *raiz);
void gerar_codigo_stmts(lista *l, no_arvore * no_stmts);
void gerar_codigo_stmt(lista *l, no_arvore * no);
void gerar_codigo_decl(lista *l, no_arvore * no);
void gerar_codigo_cond(lista *l, no_arvore * no);
void gerar_codigo_logic(lista *l ,no_arvore *raiz);


char * gerar_codigo_expr(lista *l, no_arvore *raiz);
void gerar_codigo_attr(lista *l, no_arvore *raiz);

char * mapear_tipo(int tipo);

#endif