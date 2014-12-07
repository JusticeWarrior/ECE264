#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer11.h"

StackNode * StackNode_Create(HuffNode * tree);
void StackNode_Deconstruct(StackNode * node);

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
	Stack * stack = malloc(sizeof(Stack));
	stack->head = NULL;

	return stack;
}

void Stack_destroy(Stack * stack)
{
	if (stack == NULL) // If stack contains nothing free it and be done.
		return;

	// Free all memory associated with the contained linked-list
	while (stack->head != NULL)
	{
		StackNode * next = stack->head->next;
		HuffNode_destroy(stack->head->tree);
		StackNode_Deconstruct(stack->head);
		stack->head = next;
	}
	free(stack);
}

int Stack_isEmpty(Stack * stack)
{
	// just in case stack is considered empty if it is NULL
	if (stack == NULL)
		return 1;
	if (stack->head == NULL)
		return 1;
	return 0;
}

StackNode * StackNode_Create(HuffNode * tree)
{
	StackNode * node = malloc(sizeof(StackNode));
	node->next = NULL;
	node->tree = tree;

	return node;
}

void StackNode_Deconstruct(StackNode * node)
{
	free(node);
}

HuffNode * Stack_popFront(Stack * stack)
{
	if (Stack_isEmpty(stack))
		return NULL; // If stack is empty, we can't pop the front node.

	HuffNode * tree = stack->head->tree;
	StackNode * head = stack->head;
	stack->head = stack->head->next;
	StackNode_Deconstruct(head);

	// If tree is NULL at this point, then stack->head->tree was NULL
	return tree;
}

void Stack_pushFront(Stack * stack, HuffNode * tree)
{
	StackNode * node = StackNode_Create(tree);
	node->next = stack->head;
	stack->head = node;
}

void Stack_popPopCombinePush(Stack * stack)
{
	HuffNode * node1 = Stack_popFront(stack);
	HuffNode * node2 = Stack_popFront(stack);

	HuffNode * root = HuffNode_create(node1->value + node2->value);
	root->left = node1;
	root->right = node2;

	Stack_pushFront(stack, root);
}

HuffNode * HuffTree_readTextHeader(FILE * fp)
{
	Stack * stack = Stack_create();
	char position = fgetc(fp);
	HuffNode * node = NULL;
	while (!feof(fp))
	{
		if (position == '1')
		{
			position = fgetc(fp);
			node = HuffNode_create(position);
			Stack_pushFront(stack, node);
		}
		else
		{
			if (stack->head == NULL || stack->head->next == NULL)
				break;
			Stack_popPopCombinePush(stack);
		}
		position = fgetc(fp);
	}
	node = Stack_popFront(stack);

	Stack_destroy(stack);

	return node;
}

HuffNode * HuffTree_readBinaryHeader(FILE * fp)
{
	return NULL;
}