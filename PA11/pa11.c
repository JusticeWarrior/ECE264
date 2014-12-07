#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer11.h"

extern StackNode * StackNode_Create(HuffNode * tree);
extern void StackNode_Deconstruct(StackNode * node);

int main(int argc, char * * argv)
{
	Stack * stack = Stack_create();

	HuffNode * tree = HuffNode_create(5);
	tree->left = HuffNode_create(6);
	tree->left->right = HuffNode_create(7);

	StackNode * node1 = StackNode_Create(tree);

	HuffNode * tree2 = HuffNode_create(5);
	tree2->right = HuffNode_create(6);
	tree2->left->left = HuffNode_create(7);

	StackNode * node2 = StackNode_Create(tree2);

	HuffNode * tree3 = HuffNode_create(5);
	tree3->left = HuffNode_create(6);
	tree3->left->left = HuffNode_create(7);

	StackNode * node3 = StackNode_Create(tree3);

	stack->head = node1;
	stack->head->next = node2;
	stack->head->next->next = node3;

	HuffNode * pop = Stack_popFront(stack);
	Stack_pushFront(stack, pop);

	Stack_destroy(stack);

	return EXIT_SUCCESS;
}