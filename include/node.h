#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "table.h"

// list of node types
enum
{
	K_PROGRAM,    // 0
	K_STATEMENTS, // 1
	K_PRINT,      // 2
	K_INPUT,      // 3
	K_WHILE,      // 4
	K_DO_WHILE,   // 5
	K_IF,         // 6
	K_IF_ELSE,    // 7
	K_ELSE,       // 8
	K_ADD,        // 9
	K_SUB,        // 10
	K_MULT,       // 11
	K_DIV,        // 12
	K_MOD,        // 13
	K_NEG,        // 14
	K_POSITIVE,   // 15
	K_MORE,       // 16
	K_LESS,       // 17
	K_MOREEQ,     // 18
	K_LESSEQ,     // 19
	K_EQUAL,      // 20
	K_NOT_EQUAL,  // 21
	K_AND,        // 22
	K_OR,         // 23
	K_VAR,        // 24
	K_NUM,        // 25
	K_NONE,       // 26
	K_EXPR,       // 27
	K_STRING,     // 28
	K_PLUSA,      // 29
	K_MINUSA,     // 30
	K_MULTA,      // 31
	K_DIVA,       // 32
	K_MODA,       // 33
	K_ASSIGN,     // 34
	K_INIT_VARS,  // 34
};

typedef struct node
{
	int kind;
	int value;
	char *str;
	Symbol *symbol;

	struct node *lhs; // left-hand side
	struct node *rhs; // right-hand side

	Vector *node_list;
}
Node;

void  start_print_node (Node *node);
Node *new_node         (int kind);

#endif