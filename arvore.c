#include <stdlib.h>
#include <stdio.h>
#include "arvore.h"
#include "y.tab.h"

no_arvore * criar_no_expressao(int op, void *dir, void *esq) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipo = EXPR;
	novo->dado.expr =  criar_expressao(op, dir, esq);
	return novo;
}

/*a direita e esquerda são do tipo void pois podem ser tanto número quanto 
ID, então pode receber dos 2 tempos*/
t_expr * criar_expressao(int op, void *dir, void *esq) {
	t_expr * novo = (t_expr *) malloc(sizeof(t_expr));
	novo->op = op;
	novo->dir = dir;
	novo->esq = esq;
	return novo;
}

no_arvore * criar_no_atribuicao(simbolo *resultado, void *expressao) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipo = ATTR;
	novo->dado.attr =  criar_atribuicao(resultado, expressao);
	return novo;
}
/* Simbolo *resultado se refere ao identificador onde a expressão será salva */
t_attr * criar_atribuicao(simbolo *resultado, void *expressao){ 
	t_attr * novo = (t_attr *) malloc(sizeof(t_attr));
	novo->resultado = resultado;
	novo->expressao = expressao;
	return novo;
}


no_arvore * criar_no_statement(void *stmt) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipo = STMT;
	novo->dado.stmt =  criar_statement(stmt);
	return novo;
}
t_stmt * criar_statement(void *stmt){ 
	t_stmt * novo = (t_stmt *) malloc(sizeof(t_stmt));
	novo->declaracao = stmt;
	return novo;
}


no_arvore * criar_no_statements(void *stmts, void *stmt) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipo = STMTS;
	novo->dado.stmts =  criar_statements(stmts, stmt);
	return novo;
}
t_stmts * criar_statements(void *stmts, void *stmt){ 
	t_stmts * novo = (t_stmts *) malloc(sizeof(t_stmts));
	novo->declaracao_d = stmt;
	novo->declaracao_e = stmts;
	return novo;
}

no_arvore * criar_no_bloco(void* stmts) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipo = BLOCO;
	novo->dado.bloco =  criar_bloco(stmts);
	return novo;
}
t_bloco * criar_bloco(void* stmts){ 
	t_bloco * novo = (t_bloco *) malloc(sizeof(t_bloco));
	novo->conteudo = stmts;
	return novo;
}


no_arvore * criar_no_program(void *program_e, void *program_d) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipo = PROGRAM;
	novo->dado.program =  criar_program(program_e, program_d);
	return novo;
}
t_program * criar_program(void *program_e, void *program_d){ 
	t_program * novo = (t_program *) malloc(sizeof(t_program));
	novo->program_d = program_d;
	novo->program_e = program_e;
	return novo;
}