#ifndef ARVORE_H
#define ARVORE_H

#include <string.h>
#include "tabela.h"
#include "y.tab.h"

typedef struct t_expr {
	int op;
	int tipo; //float ou int
	void *dir, *esq;
} t_expr;

typedef struct t_attr {
	simbolo *resultado;
	void *expressao;
} t_attr;

typedef struct t_stmt {
	void *declaracao;
} t_stmt;


typedef struct t_stmts {
	//O tipo da declaração a direita é o stmt
	t_stmt *declaracao_d;

	//realiza a recursão a esquerda
	struct t_stmts *declaracao_e;

} t_stmts;

typedef struct t_bloco {
	t_stmts *conteudo;
} t_bloco;

typedef struct t_program {
	t_bloco *program_d;
	struct t_program *program_e;
} t_program;


typedef union valor_sintatico {
	t_expr *expr;
	t_attr *attr;
	t_stmt *stmt;
	t_stmts *stmts;
	t_bloco *bloco;
	t_program *program;
} valor_sintatico;

typedef struct no_arvore {
	int tipo; //expr, attr, stmt, ...
	valor_sintatico dado;
	//ponteiro para tabela de símbolos
} no_arvore;

no_arvore * criar_no_expressao(int op, void *dir, void *esq);
t_expr * criar_expressao(int op, void *dir, void *esq);

no_arvore * criar_no_atribuicao(simbolo *resultado, void *expressao);
t_attr * criar_atribuicao(simbolo *resultado, void *expressao);

no_arvore * criar_no_statement(void *stmt);
t_stmt * criar_statement(void *stmt);

no_arvore * criar_no_statements(void *stmts, void *stmt);
t_stmts * criar_statements(void *stmts, void *stmt);

no_arvore * criar_no_bloco(void *stmts);
t_bloco * criar_bloco(void *stmts);

no_arvore * criar_no_program(void *program_e, void *program_d);
t_program * criar_program(void *program_e, void *program_d);


#endif
