#ifndef COMP_TREE_H
#define COMP_TREE_H

typedef struct comp_tree_t {
	int data;
	struct comp_tree_t left;
	struct comp_tree_t right;
} TreeNode;

TreeNode* createTree();
TreeNode* freeTree(TreeNode* root);
TreeNode* insertTree(TreeNode** root, int data);
void printTree(TreeNode* root);
TreeNode* searchNode(TreeNode** root, int data);

#endif

