#include "avl.h"

void makeNullTree(tree_type *tree) {
	(*tree) = NULL;
}

TNode *makeTNode(element_type val) {
	TNode *p;
	p = (TNode *)malloc(sizeof(TNode));
	p->left = NULL;
	p->right = NULL;
	p->info = val;
	p->height = 1;
	return p;
}

int emptyTree(tree_type tree) {
	return tree == NULL;
}

int height(tree_type tree)
{
	if (tree == NULL)
		return 0;
	return tree->height;
}

int getBalance(tree_type tree) {
	if (tree == NULL)
		return 0;
	return height(tree->left) - height(tree->right);
}

int max(int a, int b) {
	return a > b ? a : b;
}

void rotateLeft(tree_type *tree) {
	tree_type right = (*tree)->right;

	(*tree)->right = right->left;
	right->left = *tree;

	(*tree)->height =	max(height((*tree)->left), height((*tree)->right)) + 1;
	right->height = max(height(right->left), height(right->right)) + 1;

	*tree = right;
}

void rotateRight(tree_type *tree) {
	tree_type left = (*tree)->left;

	(*tree)->left = left->right;
	left->right = *tree;

	(*tree)->height =	max(height((*tree)->left), height((*tree)->right)) + 1;
	left->height = max(height(left->left), height(left->right)) + 1;

	*tree = left;
}

void freeTree(tree_type tree) {
	if (emptyTree(tree))
		return;
	freeTree(tree->left);
	freeTree(tree->right);
	free(tree);
	return;
}

tree_type findMin(tree_type tree) {
	if (tree == NULL)
		return NULL;
	else if (tree->left != NULL)
		return findMin(tree->left);
	else
		return tree;
}

tree_type findMax(tree_type tree) {
	if (tree == NULL)
		return NULL;
	else if (tree->right != NULL)
		return findMax(tree->right);
	else
		return tree;
}

tree_type search(tree_type tree, key_type key) {
	if (tree == NULL)
		return NULL;
	else if (tree->info.key == key)
		return tree;
	else if (key < tree->info.key)
		tree = search(tree->left, key);
	else
		tree = search(tree->right, key);
}


void insert(tree_type *tree, element_type entry) {
	if (*tree == NULL)
		*tree = makeTNode(entry);
	else if ((*tree)->info.key > entry.key)
		insert(&(*tree)->left, entry);
	else if ((*tree)->info.key < entry.key)
		insert(&(*tree)->right, entry);

	(*tree)->height = max(height((*tree)->left), height((*tree)->right)) + 1;

	int balance = getBalance(*tree);

	if (balance > 1)
		if (entry.key < (*tree)->left->info.key) //left-left
			rotateRight(tree);
		else if (entry.key > (*tree)->left->info.key) //left-right
		{
			rotateLeft(&(*tree)->left);
			rotateRight(tree);
		}
	if (balance < -1)
		if (entry.key > (*tree)->right->info.key) //right-right
			rotateLeft(tree);
		else if (entry.key < (*tree)->right->info.key)//right-left
		{
			rotateRight(&(*tree)->right);
			rotateLeft(tree);
		}
}

element_type deleteMin (tree_type *tree ) {
	element_type key;
	if ((*tree)->left == NULL) {
		key = (*tree)->info;
		(*tree) = (*tree)->right;
		return key;
	}
	else return deleteMin(&(*tree)->left);
}

void delete(tree_type *tree, key_type key)
{
	if (*tree != NULL)
	{
		if (key < (*tree)->info.key)
			delete(&(*tree)->left, key);
		else if (key > (*tree)->info.key)
			delete(&(*tree)->right, key);
		else if ((*tree)->left == NULL && (*tree)->right == NULL)
			*tree = NULL;
		else if ((*tree)->left == NULL)
			*tree = (*tree)->right;
		else if ((*tree)->right == NULL)
			*tree = (*tree)->left;
		else
			(*tree)->info = deleteMin(&(*tree)->right);
	}
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

void reinOrder(tree_type tree, void (*order)(tree_type))
{
	if (tree != NULL)
	{
		reinOrder(tree->right, order);
		order(tree);
		reinOrder(tree->left, order);
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