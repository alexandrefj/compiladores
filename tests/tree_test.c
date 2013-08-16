#include <stdio.h>
#include <stdlib.h>

#include "comp_tree.h"

int main()
{
	printf("\n");

	TreeNode* tree = createTree();

	insertTree(&tree, 5);
	insertTree(&tree, 1);
	insertTree(&tree, 3);
	insertTree(&tree, 4);
	insertTree(&tree, 2);

	printTree(tree);

	tree = searchNode(&tree, 3);
	printf("\n%d\n", tree->data);

	freeTree(tree);

	printf("\n");

	return 0;
}

