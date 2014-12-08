#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer11.h"
#include "stdint.h"

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
	root->left = node2;
	root->right = node1;

	Stack_pushFront(stack, root);
}

HuffNode * HuffTree_readTextHeader(FILE * fp)
{
	Stack * stack = Stack_create();
	char position = fgetc(fp);
	HuffNode * node = NULL;
	while (1)
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
	Stack * stack = Stack_create();
	HuffNode * node = NULL;

	uint8_t positionBits[2];
	uint8_t character = 0x00;
	fread(&positionBits[0], sizeof(uint8_t), 2, fp);
	while (1)
	{
		int i;
		for (i = 7; i >= 0; --i)
		{
			if (((positionBits[0] >> i) & 0x01) == 0x01)
			{
				i--; // Move to the position of the first bit of the character
				int bit;
				for (bit = 7; bit >= 0; bit--)
				{
					if (i >= 0)
					{
						//Assign value of character bit
						if (((positionBits[0] >> i) & 0x01) == 0x01)
						{
							(character | (0x01 << bit));
						}
						else
						{
							(character & ~(0x01 << bit));
						}
						
					}
					else
					{
						positionBits[0] = positionBits[1];
						fread(&positionBits[1], sizeof(uint8_t), 1, fp);
						i = 7;

						//Assign value of character bit
						if (((positionBits[0] >> i) & 0x01) == 0x01)
						{
							(character | (0x01 << bit));
						}
						else
						{
							(character & ~(0x01 << bit));
						}
					}
					i--;
				}
				node = HuffNode_create(character);
				Stack_pushFront(stack, node);
			}
			else
			{
				if (stack->head == NULL || stack->head->next == NULL)
				{
					node = Stack_popFront(stack);
					Stack_destroy(stack);
					return node;
				}
				Stack_popPopCombinePush(stack);
			}
		}
		positionBits[0] = positionBits[1];
		fread(&positionBits[1], sizeof(uint8_t), 1, fp);
	}

	node = Stack_popFront(stack);

	Stack_destroy(stack);

	return node;
}