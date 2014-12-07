#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer11.h"

HuffNode * HuffNode_create(int value)
{
	HuffNode* node = malloc(sizeof(HuffNode));

	node->left = NULL;
	node->right = NULL;

	node->value = value;

	return node;
}

void HuffNode_destroy(HuffNode * tree)
{
	if (tree == NULL)
		return;
	HuffNode_destroy(tree->left);
	HuffNode_destroy(tree->right);

	free(tree);
}

Stack * Stack_create()
{
	return NULL;
}

void Stack_destroy(Stack * stack)
{
}

int Stack_isEmpty(Stack * stack)
{
	return 0;
}

HuffNode * Stack_popFront(Stack * stack)
{
	return NULL;
}

void Stack_pushFront(Stack * stack, HuffNode * tree)
{
}

void Stack_popPopCombinePush(Stack * stack)
{
}

HuffNode * HuffTree_readTextHeader(FILE * fp)
{
	return NULL;
}

HuffNode * HuffTree_readBinaryHeader(FILE * fp)
{
	return NULL;
}