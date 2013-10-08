#ifndef COMP_TREE_H
#define COMP_TREE_H


#define MAX_NODE  4

#include <stdio.h>
#include <stdlib.h>
#include "comp_dict.h"
#include "iks_ast.h"
#include "gv.h"

typedef struct astreenode
{
	int type;
	int node_type;
	int size;
	DICT_NODE *symbol;
	struct astreenode *scc[MAX_NODE];
	int read;
}ASTREE; 

ASTREE *astCreate(int type, DICT_NODE *symbol, ASTREE *s0, ASTREE *s1, ASTREE *s2, ASTREE *s3);
void *astReadTree(ASTREE *root);
void *astReadNode(ASTREE *node);

#endif

