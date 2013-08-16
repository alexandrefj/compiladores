#ifndef COMP_TREE_H
#define COMP_TREE_H

/*
TreeNode: Representa cada nodo da arvore. Contem um
valor inteiro, um filho a esquerda, e um filho a
direita.
*/
typedef struct comp_tree_t {
	int data;
	struct comp_tree_t* left;
	struct comp_tree_t* right;
} TreeNode;

/*
createTree: Inicializa uma arvore com um nodo vazio.
*/
TreeNode* createTree();

/*
freeTree: Libera o espaco alocado por uma arvore.
*/
void freeTree(TreeNode* root);

/*
insertTree: Insere um valor inteiro em uma arvore.
*/
void insertTree(TreeNode** root, int data);

/*
printTree: Imprime todos os valores da arvore em
ordem crescente.
*/
void printTree(TreeNode* root);

/*
searchNode: Procura um valor na arvore. Retorna o
nodo que contem o valor, ou NULL caso o valor nao
pertenca a arvore.
*/
TreeNode* searchNode(TreeNode** root, int data);

#endif
