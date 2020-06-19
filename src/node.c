#include "../include/node.h"

static char *prefix;

Node *new_node(int kind)
{
	Node *node = malloc(sizeof(Node));

	node->kind      = kind;
	node->value     = 0;
	node->symbol    = NULL;
	node->lhs       = NULL;
	node->rhs       = NULL;
	node->node_list = NULL;

	return node;
}

static void print_kind(Node *n)
{
	switch (n->kind)
	{
		case K_ADD:        printf("+\n");                 break;
		case K_SUB:        printf("-\n");                 break;
		case K_MULT:       printf("*\n");                 break;
		case K_DIV:        printf("/\n");                 break;
		case K_MOD:        printf("%%\n");                break;
		case K_MORE:       printf(">\n");                 break;
		case K_LESS:       printf("<\n");                 break;
		case K_MOREEQ:     printf(">=\n");                break;
		case K_LESSEQ:     printf("<=\n");                break;
		case K_EQUAL:      printf("==\n");                break;
		case K_NOT_EQUAL:  printf("!=\n");                break;
		case K_AND:        printf("&&\n");                break;
		case K_OR:         printf("||\n");                break;
		case K_POSITIVE:   printf("+\n");                 break;
		case K_NEG:        printf("-\n");                 break;
		case K_NUM:        printf("%i\n", n->value);      break;
		case K_PROGRAM:    printf("<program>\n");         break;
		case K_NONE:       printf("none\n");              break;
		case K_STATEMENTS: printf("<statements>\n");      break;
		case K_EXPR:       printf("<expr>\n");            break;
		case K_IF:         printf("<if>\n");              break;
		case K_ELSE:       printf("<else>\n");            break;
		case K_IF_ELSE:    printf("<if-else>\n");         break;
		case K_WHILE:      printf("<while>\n");           break;
		case K_DO_WHILE:   printf("<do-while>\n");        break;
		case K_PRINT:      printf("<print>\n");           break;
		case K_INPUT:      printf("<input>\n");           break;
		case K_STRING:     printf("\"%s\"\n", n->str);    break;
		case K_ASSIGN:     printf("=\n");                 break;
		case K_PLUSA:      printf("+=\n");                break;
		case K_MINUSA:     printf("-=\n");                break;
		case K_MULTA:      printf("*=\n");                break;
		case K_DIVA:       printf("/=\n");                break;
		case K_MODA:       printf("%%=\n");               break;
		case K_INIT_VARS:  printf("<init-vars>\n");       break;
		case K_VAR:        printf("%s\n", n->symbol->name); break;
	}
}

/*
 * The '│' symbol cannot be saved to the pointer so I save '|' and output '│'.
 */
static void print_prefix(int prefix_len)
{
	for (int i = 0; i < prefix_len; i++)
	{
		if (prefix[i] == '|')
			printf("│");
		else
			printf("%c", prefix[i]);
	}
}

/*
 * Adds '|   ' or '    ' to the prefix.
 */
static void new_prefix(int prefix_len, int is_left)
{
	prefix = realloc(prefix, prefix_len + 4);

	for (int i = prefix_len; i < prefix_len + 4; ++i)
		prefix[i] = ' ';

	if (is_left)
		prefix[prefix_len] = '|';
}

void print_node(Node *node, int prefix_len, int is_left)
{
	if (node != NULL)
	{
		print_prefix(prefix_len);
		printf("%s", (is_left ? "├── " : "└── "));
		print_kind(node);

		new_prefix(prefix_len, is_left);
		prefix_len += 4;

		if (node->kind == K_STATEMENTS || node->kind == K_PRINT || node->kind == K_INIT_VARS)
		{
			for (int i = 0; i < node->node_list->length; ++i)
			{
				Node *buffer_node = node->node_list->data[i];
				/*
				 * if node in node_list is last that
				 * is_left (n->node_list_length - (i + 1))
				 * is zero
				 */
				print_node(buffer_node, prefix_len, node->node_list->length - (i + 1));
			}
		}
		else
		{
			print_node(node->lhs, prefix_len, 1);
			print_node(node->rhs, prefix_len, 0);
		}
	}
}

void start_print_node(Node *node)
{
	prefix = NULL;

	print_kind(node);

	print_node(node->rhs, 0, 0);
}

