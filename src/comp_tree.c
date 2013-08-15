#include <stdio.h>
#include <stdlib.h>

TreeNode* createTree() {
	return NULL;
}

TreeNode* freeTree(TreeNode* root) {
	if (root) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}

TreeNode* insertTree(TreeNode** root, int data) {
	if (*root == NULL) {
		*root = (TreeNode*) malloc(sizeof(TreeNode));
		(*root)->left = NULL;
		(*root)->right = NULL;
		(*root)->data = data;
	} else {
		if (data < (*root)->data)
			insertTree(&(*root)->left, data);		
		if (data > (*root)->data)
			insertTree(&(*root)->right, data);
	}
}

void printTree(TreeNode* root) {
	if (root != NULL) {
		printTree(root->left);
		printf("%d\n", root->data);
		printTree(root->right);
	}
}

TreeNode* searchNode(TreeNode** root, int data) {
	if (*root == NULL)
		return NULL;

	if (data < (*root)->data)
		searchNode(&((*root)->left), data);
	else if (data > (*root)->data)
		searchNode(&((*root)->right), data);
	else if (data == (*root)->data)
		return *root;
}

