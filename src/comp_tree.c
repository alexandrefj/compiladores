#include "comp_tree.h"



ASTREE *astCreate(int type, DICT_NODE *symbol, ASTREE *s0, ASTREE *s1, ASTREE *s2, ASTREE *s3)
{
	ASTREE *newNode;
	
	newNode = (ASTREE*)calloc(1,sizeof(ASTREE));
	newNode->type = type;
	newNode->symbol = symbol;
	newNode->scc[0] = s0;
	newNode->scc[1] = s1;
	newNode->scc[2] = s2;
	newNode->scc[3] = s3;
	newNode->read = 0;
	return newNode;
}


void *astReadTree(ASTREE *root)
{
	int i;
	if(root==NULL) return;
	astReadNode(root);
	for(i=0; i<MAX_NODE; i++)
	   astReadTree(root->scc[i]);
}

void *astReadNode(ASTREE *node)
{
	if(node==NULL) return;
	if(node->read==1)return;
	node->read = 1;
	
		
	switch(node->type){
		case IKS_AST_FUNCAO:	
		case IKS_AST_IDENTIFICADOR:
		case IKS_AST_LITERAL:
		gv_declare(node->type,node, node->symbol->text);
		break;
		default:
		gv_declare(node->type,node, NULL);
		break;
	}

	
	int i;
	for(i=0;i<MAX_NODE;i++){
		if(node->scc[i]!=NULL)
			gv_connect(node,node->scc[i]);

	}

}
