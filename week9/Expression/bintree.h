#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element_type;

typedef struct TNode {
	element_type info;
	struct TNode *left;
	struct TNode *right;
} TNode;

typedef TNode *tree_type;


void makeNullTree(tree_type *tree) {
	(*tree) = NULL;
}

TNode *makeTNode(element_type val) {
	TNode *p = NULL;
	p = (TNode *)malloc(sizeof(TNode));
	if(p == NULL)
	{
		printf("Can't allocate memory!\n");
		exit(1);
	}
	
	p->left = NULL;
	p->right = NULL;
	p->info = val;
	return p;
}

int emptyTree(tree_type tree) {
	return tree == NULL;
}

void freeTree(tree_type tree) {
	if (emptyTree(tree))
		return;
	freeTree(tree->left);
	freeTree(tree->right);
	free(tree);
	return;
}

TNode *leftChild(TNode *p) {
	if (p != NULL)
		return p->left;
	else
		return NULL;
}

TNode *rightChild(TNode *p) {
	if (p != NULL)
		return p->right;
	else
		return NULL;
}

int isLeaf(tree_type p) {
	if (p != NULL)
		if (leftChild(p) == NULL && rightChild(p) == NULL)
			return 1;
}

int countNode(tree_type tree) {
	if (emptyTree(tree))
		return 0;
	else
		return 1 + countNode(leftChild(tree)) + countNode(rightChild(tree));
}

int countLeaves(tree_type tree) {
	if (emptyTree(tree))
		return 0;
	else if (tree->left == NULL && tree->right == NULL)
		return 1;
	else
		return countLeaves(tree->left) + countLeaves(tree->right);
}

int height(tree_type tree) {
	int ld, rd;
	if (emptyTree(tree))
		return 0;
	ld = height(leftChild(tree));
	rd = height(rightChild(tree));
	return 1 + (ld > rd ? ld : rd);
}

int depth(tree_type tree, TNode *p, int d)
{
	if (tree == NULL || p == NULL) return 0;
	else if (tree == p ) return d;
	else {
		return depth(tree->left, p, d + 1) + depth(tree->right, p, d + 1);
	}
}

int nb_right(tree_type tree) {
	if (tree == NULL) return 0;
	else {
		int s = 0;
		if (tree->right != NULL) s = 1;
		return s + nb_right(tree->right) + nb_right(tree->left);
	}
}

tree_type createFrom2(element_type val, tree_type left, tree_type right)
{
	TNode *new;
	new = makeTNode(val);
	new->left = left;
	new->right = right;
	return new;
}

tree_type addtoLeftmost(tree_type *tree, element_type val)
{
	TNode *new;
	new = makeTNode(val);
	if (new == NULL)
		return new;
	if (*tree == NULL)
		*tree = new;
	else
	{
		TNode *lNode = *tree;
		while (lNode->left != NULL)
			lNode = lNode->left;
		lNode->left = new;
	}
	return new;
}

tree_type addtorightmost(tree_type *tree, element_type val)
{
	TNode *new;
	new = makeTNode(val);
	if (new == NULL)
		return new;
	if (*tree == NULL)
		*tree = new;
	else
	{
		TNode *rNode = *tree;
		while (rNode->right != NULL)
			rNode = rNode->right;
		rNode->right = new;
	}
	return new;
}

void preOrder(tree_type tree, void (*order)(tree_type))
{
	if (tree != NULL)
	{
		order(tree);
		preOrder(tree->left, order);
		preOrder(tree->right, order);
	}
}

void inOrder(tree_type tree, void (*order)(tree_type))
{
	if (tree != NULL)
	{
		inOrder(tree->left, order);
		order(tree);
		inOrder(tree->right, order);
	}
}

void postOrder(tree_type tree, void (*order)(tree_type))
{
	if (tree != NULL)
	{
		postOrder(tree->left, order);
		postOrder(tree->right, order);
		order(tree);
	}
}

void reverseTree(tree_type *tree) {
	tree_type temp;

	if (*tree != NULL) {
		if ((*tree)->left != NULL)
			reverseTree(&(*tree)->left);
		if ((*tree)->right != NULL)
			reverseTree(&(*tree)->right);
		
		temp = (*tree)->left;
		(*tree)->left = (*tree)->right;
		(*tree)->right = temp;
	}
}

// tree_type constructTree(element_type preval, element_type preLN[], int *index_ptr, int n) {
// 	int index = *index_ptr;
// 	element_type *s;
// 	if (index == n)
// 		return NULL;
// 	TNode *temp;
// 	s = (element_type *)preval;
// 	temp = makeTNode(s + index * 10);
// 	(*index_ptr)++;
// 	if (preLN[index] == 'N')
// 	{
// 		temp->left = constructTree(preval, preLN, index_ptr, n);
// 		temp->right = constructTree(preval, preLN, index_ptr, n);
// 	}
// 	return temp;
// }

// tree_type buildTree(element_type preval, element_type preLN[], int n) {
// 	int index = 0;
// 	return constructTree(preval, preLN, &index, n);
// }
