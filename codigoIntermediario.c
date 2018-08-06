#include <stdlib.h>
#include <stdio.h>
#include "y.tab.h"
#include "codigoIntermediario.h"

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

//Aloca as instruções na struct e retorna o endereço dessa instrução
instrucao * criar_instrucao( int opcode, void *resultado, void *esq, void *dir){
	instrucao *temp = (instrucao *) malloc(sizeof(instrucao));
	
	temp->opcode = opcode;
	temp->resultado = resultado;
	temp->esq = esq;
	temp->dir = dir;
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

//Inicializa a lista e retorna seu endereço
lista * inicializar_lista (){
	lista *temp = (lista *) malloc(sizeof(lista));
	//no_lista *cursor  = (no_lista *) malloc(sizeof(no_lista));
	//temp->primeiro = cursor;
	return temp;
}


//Imprime toda a lista, de forma linear
void imprimir_lista(lista *l){

	no_lista *cursor  = (no_lista *) malloc(sizeof(no_lista));
	cursor = l->primeiro;
	if(cursor == NULL)
		printf("Lista vazia");
	do{
		printf("======%d\n", cursor->dado->opcode);
		cursor = cursor->proximo;
	//Estava dando erro aqui, cuidado para não instanciar um apontador de um null( proximo de um proximo)
	}while(cursor != NULL);
	printf("fim do imprimir_lista\n");
}
