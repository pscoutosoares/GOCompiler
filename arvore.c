#include <stdlib.h>
#include <stdio.h>
#include "arvore.h"
#include "y.tab.h"

///////////////////////Expr//////////////////////////////////////////
no_arvore * criar_no_expressao(int op, void *dir, void *esq) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipo = LOGIC;
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

///////////////////////Attr//////////////////////////////////////////
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

///////////////////////Logic//////////////////////////////////////////
no_arvore * criar_no_logic(int op, void *dir, void *esq) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipo = LOGIC;
	novo->dado.logic =  criar_logic(op, dir, esq);
	return novo;
}
t_logic * criar_logic(int op, void *dir, void *esq){ 
	t_logic * novo = (t_logic *) malloc(sizeof(t_logic));
	novo->op = op;
	novo->dir = dir;
	novo->esq = esq;
	return novo;
}

///////////////////////Stmt//////////////////////////////////////////
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

///////////////////////Stmts//////////////////////////////////////////
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

///////////////////////Decl//////////////////////////////////////////
no_arvore * criar_no_decl(int tipo, simbolo *id) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipo = DECL;
	novo->dado.decl =  criar_decls(tipo, id);
	return novo;
}
t_decl * criar_decls(int tipo, simbolo *id){ 
	t_decl * novo = (t_decl *) malloc(sizeof(t_decl));
	novo->tipo = tipo;
	novo->id = id;
	return novo;
}

///////////////////////Bloco//////////////////////////////////////////
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

///////////////////////Program///////////////////////////////////////
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


///////////////////////Cond///////////////////////////////////////
no_arvore * criar_no_cond(void *cond_logica, void *cond_if, void *cond_else) {
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipo = COND;
	novo->dado.cond =  criar_cond(cond_logica, cond_if, cond_else);
	return novo;
}
t_cond * criar_cond(void *cond_logica, void *cond_if, void *cond_else){ 
	t_cond * novo = (t_cond *) malloc(sizeof(t_cond));
	novo->cond_logica = cond_logica;
	novo->cond_if = cond_if;
	novo->cond_else = cond_else;
	return novo;
}


///////////////////////Loop//////////////////////////////////////
no_arvore * criar_no_loop(void *loop_logica, void *loop_bloco){
	no_arvore *novo = (no_arvore *)  malloc(sizeof(no_arvore));
	novo->tipo = LOOP;
	novo->dado.loop =  criar_loop(loop_logica, loop_bloco);
	return novo;
}
t_loop * criar_loop(void *loop_logica, void *loop_bloco){ 
	t_loop * novo = (t_loop *) malloc(sizeof(t_loop));
	novo->loop_logica = loop_logica;
	novo->loop_bloco = loop_bloco;
	return novo;
}

