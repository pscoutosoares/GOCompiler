#ifndef CODIGO_INTERMEDIARIO_H
#define CODIGO_INTERMEDIARIO_H

#include "arvore.h"
#include <string.h>

typedef struct instrucao{
	//Opcode recebe o tipo de no_arovre
	int opcode;
	// as variaveis void recebem apontadores das suas respectivas estruturas
	void *resultado, *esq, *dir;
}instrucao;

typedef struct no_lista {
	instrucao *dado;
	struct no_lista *proximo;
} no_lista;

typedef struct lista {
	no_lista *primeiro;
} lista;


void inserir_no_lista(lista *l, instrucao *inst);
instrucao * criar_instrucao( int opcode, void *resultado, void *esq, void *dir);
no_lista * ultimo_no(lista *l);
lista * inicializar_lista();
void imprimir_lista(lista *l);

void gerar_codigo(no_arvore * raiz);
char * gerar_codigo_expr(no_arvore *raiz);
void gerar_codigo_attr(no_arvore *raiz);

#endif