#ifndef CODIGO_INTERMEDIARIO_H
#define CODIGO_INTERMEDIARIO_H

#include "arvore.h"
#include "y.tab.h"

typedef struct instrucao{
	int opcode;
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

#endif