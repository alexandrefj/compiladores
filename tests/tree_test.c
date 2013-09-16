#include <stdio.h>
#include <stdlib.h>

#include "comp_tree.h"


int main()
{
	ASTREE* root,*ast1,*ast2,*ast3,*ast4,*ast5,*ast6;

	//DICT_NODE *symbol = malloc(sizeof(DICT_NODE*));

	ast1=astCreate(5,0,0, 0, 0, 0);

	ast2=astCreate(6,0,0, 0, 0, 0);

	ast3=astCreate(7,0,0, 0, 0, 0);

	ast4=astCreate(7,0,0, 0, 0, 0);

	ast5=astCreate(7,0,0, 0, 0, 0);

	ast6=astCreate(7,0,0, 0, 0, 0);

	ast4=astCreate(7,0,0, ast5, ast6, 0);

	root=astCreate(5,0,ast1, ast2, ast3, ast4);

	//------------------------------------------------

	gv_init("testando.dot");

	astReadTree(root);


	gv_close();


	return 0;
}

