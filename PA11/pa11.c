#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer11.h"

int main(int argc, char * * argv)
{
	HuffNode * node = HuffNode_create(5);
	node->left = HuffNode_create(6);
	node->left->right = HuffNode_create(7);

	HuffNode_destroy(node);

	return EXIT_SUCCESS;
}